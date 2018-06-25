
#include "square-Graphscene.h"
#include "square-GraphEdge.h"
#include "square-GraphVertex.h"
#include "square-GraphTextItem.h"
#include "square-GraphItem.h"

#include <QTextCursor>
#include <QGraphicsSceneMouseEvent>
#include <QAction>
#include <QDebug>


/* ------------------------------------------------------------------ [PUBLIC] */

GraphScene::GraphScene(QMenu *_itemMenu, QObject *_parent) : QGraphicsScene(_parent), itemMenu_(_itemMenu) {


}

void GraphScene::setLineColor(const QColor &_color) {

    if (isSelectedItemofType(GraphEdge::Type)) {

        GraphEdge *edge(qgraphicsitem_cast<GraphEdge *>(selectedItems().first())); {
                   edge->item()->fillColor = _color;
        }
        
		update();
    }
}

void GraphScene::setTextColor(const QColor &_color) {

    if (isSelectedItemofType(GraphTextItem::Type)) {

        GraphTextItem *textItem(qgraphicsitem_cast<GraphTextItem *>(selectedItems().first())); {
                       textItem->setDefaultTextColor(_color);
        }
    }
}

void GraphScene::setItemColor(const QColor &_color) {

    if (isSelectedItemofType(GraphVertex::Type)) {

        GraphVertex *vertexItem(qgraphicsitem_cast<GraphVertex *>(selectedItems().first())); {
                     vertexItem->item()->fillColor = _color;
        }
		update();
    }
}

void GraphScene::setFont(const QFont &_font) {

    if (isSelectedItemofType(GraphTextItem::Type)) {

        QGraphicsTextItem *textItem(qgraphicsitem_cast<GraphTextItem *>(selectedItems().first()));
        //At this point the selection can change so the first selected item might not be a GraphTextItem

        if (textItem) {
            textItem->setFont(_font);
        }
    }
}

/* ------------------------------------------------------------------ [PUBLIC SLOTS] */

void GraphScene::slot_LostFocusTextEditor(GraphTextItem *_item) {

    QTextCursor cursor(_item->textCursor()); {
                cursor.clearSelection();    
    }
	
	_item->setTextCursor(cursor);

    if (_item->toPlainText().isEmpty()) {

        removeItem(_item);
        _item->deleteLater();
    }
}

/* ------------------------------------------------------------------ [PROTECTED] */

void GraphScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) {


}

void GraphScene::mousePressEvent(QGraphicsSceneMouseEvent *_mouseEvent) {

	if (_mouseEvent->button() != Qt::LeftButton) {

		return;
	}

	mousePressPoint_ = _mouseEvent->scenePos();

	switch (mode_) {

		case MOVE: { break; }
		
		case INSERT_VERTEX: { 

			GraphVertex *vertexItem(new GraphVertex(itemMenu_)); {

				vertexItem->setPos(_mouseEvent->scenePos());
			}

			addItem(vertexItem);
			break;
		}

		case INSERT_EDGE: {

		//	line_ = new QGraphicsLineItem(QLineF(_mouseEvent->scenePos(), _mouseEvent->scenePos()));

			line_ = new QGraphicsLineItem();


			addItem(line_);
			break;
		}

		case INSERT_TEXT: {

			GraphTextItem *textItem(new GraphTextItem()); {

				textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
				textItem->setZValue(1000.0);
				textItem->setPos(_mouseEvent->scenePos());

				connect(textItem, SIGNAL(signal_LostFocus(GraphTextItem*)), this, SLOT(slot_LostFocusTextEditor(GraphTextItem*)));
				connect(textItem, SIGNAL(signal_SelectionChange(QGraphicsItem*)), this, SIGNAL(signal_FocusTextEditer(QGraphicsItem*)));
			}

			addItem(textItem);
			emit signal_ItemInserted();
			break;
		}

		default: break;
	}

	QGraphicsScene::mousePressEvent(_mouseEvent);
}

void GraphScene::mouseMoveEvent(QGraphicsSceneMouseEvent *_mouseEvent) {

    switch (mode_) {

        case INSERT_EDGE: { //breaks
			//qDebug() << "graphscene::mouseMoveEvent";

			//line_ = new QGraphicsLineItem(QLineF(_mouseEvent->scenePos(), _mouseEvent->scenePos()));


			if (line_) {
				//line_->setLine(QLineF(line_->line().p1(), _mouseEvent->scenePos()));
				line_->setLine(QLineF(mousePressPoint_, _mouseEvent->scenePos()));
			}
            break;
        }
        case MOVE: {

            QGraphicsScene::mouseMoveEvent(_mouseEvent);
            break;
        }

        case INSERT_VERTEX: { break; }
        case INSERT_TEXT: { break; }
        case EDIT: { break; }
        default: { break; }
    }
}

void GraphScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *_mouseEvent) {

	switch (mode_) {

		case MOVE: {

			QGraphicsScene::mouseMoveEvent(_mouseEvent);
			break;
		}

		case INSERT_EDGE: {

			if (line_) {

				QList<QGraphicsItem *> startItems(items(line_->line().p1())); {

					if (startItems.count() &&
						startItems.first() == line_) {

						startItems.removeFirst();
					}
				}

				QList<QGraphicsItem *> endItems(items(line_->line().p2())); {

					if (endItems.count() &&
						endItems.first() == line_) {

						endItems.removeFirst();
					}
				}

				removeItem(line_);
				delete line_;

				if (
					(startItems.count() > 0) &&
					(endItems.count() > 0) && //why is this one &?
					(startItems.first()->type() == GraphVertex::Type) &&
					(endItems.first()->type() == GraphVertex::Type) &&
					(startItems.first() != endItems.first())
					) {

					GraphVertex *startItem(qgraphicsitem_cast<GraphVertex *>(startItems.first()));
					GraphVertex *endItem(qgraphicsitem_cast<GraphVertex *>(endItems.first()));

					GraphEdge *arrow(new GraphEdge(startItem, endItem)); {

						arrow->setZValue(-1000.0);
						arrow->updatePosition();

						startItem->addEdge(arrow);
						endItem->addEdge(arrow);

						addItem(arrow);
						//  emit signal_InsertItem(line_);
						emit signal_ItemInserted();


					}
				}
			}

			else {
				line_ = 0;
				QGraphicsScene::mouseReleaseEvent(_mouseEvent);
			}

			break;
		}

		case INSERT_VERTEX: {
			emit signal_ItemInserted();
			break;
		}
		case INSERT_TEXT: { break; }
		case EDIT: { break; }
		default: { break; }
	}
}

/* ------------------------------------------------------------------ [PRIVATE] */

bool GraphScene::isSelectedItemofType(int _type) {

    foreach(QGraphicsItem *gitem, selectedItems()) {

        if (gitem->type() == _type) {

            return true;
        }
    }

    return false;
}