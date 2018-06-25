
/* |INCLUDES:  |QT| */
#include <QSlider>
#include <QGraphicsView>
#include <QAction>
#include <QToolBar>
#include <QtWidgets>
#include <QComboBox>
#include <QButtonGroup>
#include <Qsplitter>
#include <QLabel>

/* |INCLUDES:  |SQUARE| */
#include "square.h"
#include "square-Frame.h"

/* |INCLUDES:  |PROJECT| */
#include "square-GraphNode.h"
#include "square-GraphEdge.h"
#include "square-GraphVertex.h"
#include "square-GraphTextItem.h"

#include "square-GraphScene.h"
#include "square-GraphFrame.h"

const QSize buttonSize(QSize(50, 50));
const QString imagePath("assets:S2-GraphModel/images/");

GraphFrame::GraphFrame() : FrameInterface() {

	insert_Widget(create_ModeToolBar(), FrameInterface::HEADER);
	insert_Widget(create_ColorToolBar(), FrameInterface::HEADER);
	insert_Widget(create_EditToolBar(), FrameInterface::HEADER);
	insert_Widget(create_TextToolBar(), FrameInterface::HEADER);
	insert_Widget(create_ZoomToolBar(), FrameInterface::HEADER);

	 /* ------------------------------------------------ Item Menu: passed to the vertex item [right click menu] */

	itemMenu_ = new QMenu("Item"); {

		itemMenu_->addAction(action_ItemDelete());
		itemMenu_->addSeparator();
		itemMenu_->addAction(action_ItemToFront());
		itemMenu_->addAction(action_ItemToBack());
	}

	/* ------------------------------------------------ Scene (model): container for data items in memory */

	scene_ = new GraphScene(itemMenu_, this); {

		scene_->setSceneRect(QRectF(0, 0, 5000, 5000));

		/* ------------------------------------------ CONNECT: Reset mouse to pointer after inserting an item */

		connect(scene_, &GraphScene::signal_ItemInserted, [=] () { pointerButton_->click(); });

		/* ------------------------------------------ CONNECT: User is interacting with the text editor */

		connect(scene_, &GraphScene::signal_FocusTextEditer, [=] (QGraphicsItem *_item) {

			GraphTextItem *textItem(qgraphicsitem_cast<GraphTextItem *>(_item)); {

				QFont font(textItem->font());

				fontCombo_->setCurrentFont(font);
				fontSizeCombo_->setEditText(QString().setNum(font.pointSize()));
				boldAction_->setChecked(font.weight() == QFont::Bold);
				italicAction_->setChecked(font.italic());
				underlineAction_->setChecked(font.underline());
			}
		});
	}

	/* ------------------------------------------------ View: what the user sees */

	view_ = new QGraphicsView(scene_); {

		view_->setBackgroundBrush(QImage(imagePath + "background.jpg"));
		view_->setDragMode(QGraphicsView::RubberBandDrag);
		view_->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
		view_->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
		view_->setCacheMode(QGraphicsView::CacheBackground);
		view_->setRenderHint(QPainter::Antialiasing, false);
		view_->setRenderHints(view_->renderHints()
							  | QPainter::Antialiasing
							  | QPainter::SmoothPixmapTransform);

		insert_Widget(view_, FrameInterface::BODY);
	}

	/* ------------------------------------------------ (Zoom Slider) */

	zoomSlider_ = new QSlider(Qt::Horizontal); {

		zoomSlider_->setMinimum(0);
		zoomSlider_->setMaximum(500);
		zoomSlider_->setValue(250);
		zoomSlider_->setTickPosition(QSlider::TicksRight);

		/* ------------------------------------------ CONNECT: Zooming the scene causes everything to scale */

		connect(zoomSlider_, &QSlider::valueChanged, [=] (int) { build_Matrix(); });

		insert_Widget(zoomSlider_, FrameInterface::FOOTER);
	}

	build_Matrix();
}


void GraphFrame::set_ResetActionEnabled(bool _status) {

	if (zoomResetAction_) {

		zoomResetAction_->setEnabled(_status);
	}
}

void GraphFrame::build_Matrix() {

	qreal scale(qPow(qreal(2), (zoomSlider_->value() - 250) / qreal(50)));

	QMatrix matrix; {
		matrix.scale(scale, scale);
	}

	view_->setMatrix(matrix);
	set_ResetActionEnabled(true);
}


/* --------------------------------------------------- [PRIVATE SLOTS] */

void GraphFrame::slot_UpdateTextColor() {

	textAction_ = qobject_cast<QAction *>(sender());
	fontColorButton_->setIcon(create_ColorToolButtonIcon(imagePath + "textpointer.png", qvariant_cast<QColor>(textAction_->data())));
//	item_FontColorButton_->setIcon(create_ColorToolButtonIcon(imagePath + "textpointer.png", qvariant_cast<QColor>(textAction_->data())));

	slot_TextButtonTriggered();
}

void GraphFrame::slot_UpdateItemColor() {

	fillAction_ = qobject_cast<QAction *>(sender());
	fillColorButton_->setIcon(create_ColorToolButtonIcon(imagePath + "floodfill.png", qvariant_cast<QColor>(fillAction_->data())));
	//item_FillColorButton_->setIcon(create_ColorToolButtonIcon(imagePath + "floodfill.png", qvariant_cast<QColor>(fillAction_->data())));

	slot_FillButtonTriggered();
}

void GraphFrame::slot_updateLineColor() {

	lineAction_ = qobject_cast<QAction *>(sender());
	lineColorButton_->setIcon(create_ColorToolButtonIcon(imagePath + "linecolor.png", qvariant_cast<QColor>(lineAction_->data())));
//	item_LineColorButton_->setIcon(create_ColorToolButtonIcon(imagePath + "linecolor.png", qvariant_cast<QColor>(lineAction_->data())));

	slot_LineButtonTriggered();
}

void GraphFrame::slot_TextButtonTriggered() {

	scene_->setTextColor(qvariant_cast<QColor>(textAction_->data()));
}

void GraphFrame::slot_FillButtonTriggered() {

	scene_->setItemColor(qvariant_cast<QColor>(fillAction_->data()));
}

void GraphFrame::slot_LineButtonTriggered() {

	scene_->setLineColor(qvariant_cast<QColor>(lineAction_->data()));
}

void GraphFrame::slot_HandleFontChange() {

	QFont font(fontCombo_->currentFont()); {

		font.setPointSize(fontSizeCombo_->currentText().toInt());
		font.setItalic(italicAction_->isChecked());
		font.setUnderline(underlineAction_->isChecked());
		font.setWeight(boldAction_->isChecked()
					   ? QFont::Bold
					   : QFont::Normal);
	}

	scene_->setFont(font);
}

/* ------------------------------------------ (TOOLBARS) */

QToolBar* GraphFrame::create_ColorToolBar() {

	fontColorButton_ = new QToolButton; {

		fontColorButton_->setPopupMode(QToolButton::MenuButtonPopup);
		fontColorButton_->setMenu(create_ColorMenu(SLOT(slot_UpdateTextColor()), Qt::black));
		fontColorButton_->setIcon(create_ColorToolButtonIcon(imagePath + "textpointer.png", Qt::black));

		connect(fontColorButton_, SIGNAL(clicked()), this, SLOT(slot_TextButtonTriggered()));

		textAction_ = fontColorButton_->menu()->defaultAction();
	}

	fillColorButton_ = new QToolButton; {

		fillColorButton_->setPopupMode(QToolButton::MenuButtonPopup);
		fillColorButton_->setMenu(create_ColorMenu(SLOT(slot_UpdateItemColor()), Qt::white));
		fillColorButton_->setIcon(create_ColorToolButtonIcon(imagePath + "floodfill.png", Qt::white));

		connect(fillColorButton_, SIGNAL(clicked()), this, SLOT(slot_FillButtonTriggered()));

		fillAction_ = fillColorButton_->menu()->defaultAction();
	}

	lineColorButton_ = new QToolButton; {

		lineColorButton_->setPopupMode(QToolButton::MenuButtonPopup);
		lineColorButton_->setMenu(create_ColorMenu(SLOT(slot_updateLineColor()), Qt::black));
		lineColorButton_->setIcon(create_ColorToolButtonIcon(imagePath + "linecolor.png", Qt::black));

		connect(lineColorButton_, SIGNAL(clicked()), this, SLOT(slot_LineButtonTriggered()));

		lineAction_ = lineColorButton_->menu()->defaultAction();
	}

	QToolBar *colorToolBar(new QToolBar("Color", this)); {

		colorToolBar->addWidget(fontColorButton_);
		colorToolBar->addWidget(lineColorButton_);
		colorToolBar->addWidget(fillColorButton_);
	}

	return colorToolBar;
}

QToolBar* GraphFrame::create_EditToolBar() {

	QToolBar *editToolBar(new QToolBar("Edit", this)); {

		editToolBar->addAction(action_ItemDelete());
		editToolBar->addAction(action_ItemToFront());
		editToolBar->addAction(action_ItemToBack());
	}

	return editToolBar;
}

QToolBar* GraphFrame::create_TextToolBar() {

	fontCombo_ = new QFontComboBox(); {

		/* ------------------------------------------ CONNECT: update font */

		connect(fontCombo_, &QFontComboBox::currentFontChanged, [=] () { slot_HandleFontChange(); });
	}

	fontSizeCombo_ = new QComboBox; {

		for (int i = 8; i < 30; i = i + 2) {

			fontSizeCombo_->addItem(QString().setNum(i));
		}

		fontSizeCombo_->setEditable(true);
		fontSizeCombo_->setValidator(new QIntValidator(2, 64, this));

		/* ------------------------------------------ CONNECT: update font size */

		connect(fontSizeCombo_, static_cast<void (QComboBox::*)(const QString&)>(&QComboBox::currentIndexChanged), [=] () {

			slot_HandleFontChange();
		});
	}

	QToolBar *textToolBar(new QToolBar("Font", this)); {

		textToolBar->addWidget(fontCombo_);
		textToolBar->addWidget(fontSizeCombo_);

		textToolBar->addAction(action_TextBold());
		textToolBar->addAction(action_TextItalic());
		textToolBar->addAction(action_TextUnderline());
	}

	return textToolBar;
}

QToolBar* GraphFrame::create_ZoomToolBar() {

	QToolButton *zoomInButton(new QToolButton); {

		zoomInButton->setDefaultAction(action_ZoomIn(1));
		zoomInButton->setAutoRepeat(true);
		zoomInButton->setAutoRepeatInterval(33);
		zoomInButton->setAutoRepeatDelay(0);
	}

	QToolButton *zoomOutButton(new QToolButton); {

		zoomOutButton->setDefaultAction(action_ZoomOut(1));
		zoomOutButton->setAutoRepeat(true);
		zoomOutButton->setAutoRepeatInterval(33);
		zoomOutButton->setAutoRepeatDelay(0);
	}

	QComboBox *sceneScaleCombo(new QComboBox); {

		sceneScaleCombo->addItems(QStringList() << "50%" << "75%" << "100%" << "125%" << "150%");
		sceneScaleCombo->setCurrentIndex(2);

		/* ------------------------------------------ CONNECT: scale scene based on combo box selection */

		connect(sceneScaleCombo, static_cast<void (QComboBox::*)(const QString&)>(&QComboBox::currentIndexChanged), [=] (const QString _scale) {

			double newScale(_scale.left(_scale.indexOf("%")).toDouble() / 100.0);

			QMatrix oldMatrix(view_->matrix());

			view_->resetMatrix();
			view_->translate(oldMatrix.dx(), oldMatrix.dy());
			view_->scale(newScale, newScale);
		});
	}

	QToolBar *zoomToolBar(new QToolBar(this)); {

		zoomToolBar->addWidget(zoomInButton);
		zoomToolBar->addWidget(zoomOutButton);
		zoomToolBar->addAction(action_ZoomReset());
		zoomToolBar->addWidget(sceneScaleCombo);
	}

	return zoomToolBar;
}

QToolBar* GraphFrame::create_ModeToolBar() {

	pointerButton_ = new QToolButton(this); {

		pointerButton_->setCheckable(true);
		pointerButton_->setChecked(true);
		pointerButton_->setIcon(QIcon(imagePath + "pointer.png"));
	}

	QToolButton *linePointerButton(new QToolButton); {

		linePointerButton->setCheckable(true);
		linePointerButton->setIcon(QIcon(imagePath + "linepointer.png"));
	}

	QToolButton *textButton(new QToolButton); {

		textButton->setCheckable(true);
		textButton->setIcon(QIcon(imagePath + "textpointer.png"));
	}

	QToolButton *itemButton(new QToolButton); {

		itemButton->setCheckable(true);
		itemButton->setIcon(QIcon(imagePath + "box.png"));
	}

	pointerModeGroup = new QButtonGroup(this); {

		pointerModeGroup->setExclusive(true);

		pointerModeGroup->addButton(pointerButton_, int(GraphScene::MOVE));
		pointerModeGroup->addButton(linePointerButton, int(GraphScene::INSERT_EDGE));
		pointerModeGroup->addButton(textButton, int(GraphScene::INSERT_TEXT));
		pointerModeGroup->addButton(itemButton, int(GraphScene::INSERT_VERTEX));

		/* ------------------------------------------ CONNECT: update current mode */

		connect(pointerModeGroup, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
				[=] (int _item) {scene_->slot_SetMode(GraphScene::Mode(pointerModeGroup->checkedId()));
		});
	}

	QToolBar *modeToolBar(new QToolBar("Pointer type", this)); {

		modeToolBar->addWidget(pointerButton_);
		modeToolBar->addWidget(linePointerButton);
		modeToolBar->addWidget(textButton);
		modeToolBar->addWidget(itemButton);
	}

	return modeToolBar;
}

/* ------------------------------------------ (MENUS) */

//QWidget* GraphFrame::menu_ItemGUI() {
//
//	//item_FontColorButton_ = new QToolButton; {
//
//	//	item_FontColorButton_->setPopupMode(QToolButton::MenuButtonPopup);
//	//	item_FontColorButton_->setMenu(create_ColorMenu(SLOT(slot_UpdateTextColor()), Qt::black));
//	//	item_FontColorButton_->setIcon(create_ColorToolButtonIcon(imagePath + "textpointer.png", Qt::black));
//	//	item_FontColorButton_->setAutoFillBackground(true);
//
//	//	/* ------------------------------------------ CONNECT: update the selected model's color (text) */
//
//	//	connect(item_FontColorButton_, SIGNAL(clicked()), this, SLOT(slot_TextButtonTriggered()));
//	//}
//	textAction_ = fontColorButton_->menu()->defaultAction();
//
//	//item_FillColorButton_ = new QToolButton; {
//
//	//	item_FillColorButton_->setPopupMode(QToolButton::MenuButtonPopup);
//	//	item_FillColorButton_->setMenu(create_ColorMenu(SLOT(slot_UpdateItemColor()), Qt::white));
//	//	item_FillColorButton_->setIcon(create_ColorToolButtonIcon(imagePath + "floodfill.png", Qt::white));
//
//	//	/* ------------------------------------------ CONNECT: update the selected model's color (vertex) */
//
//	//	connect(item_FillColorButton_, SIGNAL(clicked()), this, SLOT(slot_FillButtonTriggered()));
//
//	//}
//	//fillAction_ = fillColorButton_->menu()->defaultAction();
//
//	//item_LineColorButton_ = new QToolButton; {
//
//	//	item_LineColorButton_->setPopupMode(QToolButton::MenuButtonPopup);
//	//	item_LineColorButton_->setMenu(create_ColorMenu(SLOT(slot_updateLineColor()), Qt::black));
//	//	item_LineColorButton_->setIcon(create_ColorToolButtonIcon(imagePath + "linecolor.png", Qt::black));
//
//	//	lineAction_ = lineColorButton_->menu()->defaultAction();
//
//	//	/* ------------------------------------------ CONNECT: update the selected model's color (edge) */
//
//	//	connect(item_LineColorButton_, SIGNAL(clicked()), this, SLOT(slot_LineButtonTriggered()));
//
//	//}
//
//
//	QComboBox *item_TextSizeCombo = new QComboBox; {
//
//		item_TextSizeCombo->setEditable(true);
//
//		for (int i = 8; i < 30; i = i + 2) {
//			item_TextSizeCombo->addItem(QString().setNum(i));
//		}
//
//		item_TextSizeCombo->setValidator(new QIntValidator(2, 64, this));
//
//		/* ------------------------------------------ CONNECT: update font size */
//
//		connect(item_TextSizeCombo, static_cast<void (QComboBox::*)(const QString&)>(&QComboBox::currentIndexChanged), [=] () {
//
//			slot_HandleFontChange();
//		});
//	}
//
//	QWidget *hframe(SQUARE_OBJ::containerH()); {
//
//		QLayout *layout(hframe->layout()); {
//
//		/*	layout->addWidget(item_FillColorButton_);
//			layout->addWidget(item_FontColorButton_);
//			layout->addWidget(item_LineColorButton_);*/
//			layout->addWidget(item_TextSizeCombo);
//			layout->addWidget(item_TextFontCombo_ = new QFontComboBox);
//		}
//	}
//
//	return hframe;
//}

//QWidget* GraphFrame::menu_ItemData() {
//
//	QGridLayout *layout(new QGridLayout); {
//
//		layout->setRowStretch(3, 10);
//		layout->setColumnStretch(2, 10);
//	}
//
//	QWidget *widget(new QWidget); {
//
//		widget->setLayout(layout);
//	}
//
//	return widget;
//}

QMenu *GraphFrame::create_ColorMenu(const char *_slot, QColor _defaultColor) {

	QList<QColor> colors(QList<QColor>()
						 << Qt::black
						 << Qt::white
						 << Qt::red
						 << Qt::blue
						 << Qt::yellow);

	QStringList names(QStringList()
					  << tr("black")
					  << tr("white")
					  << tr("red")
					  << tr("blue")
					  << tr("yellow"));

	QMenu *colorMenu(new QMenu(this)); {

		FOR_I(colors.count()) {

			QAction *action(new QAction(names.at(i), this)); {

				action->setData(colors.at(i));
				action->setIcon(create_ColorIcon(colors.at(i)));

				/* ------------------------------------------ CONNECT:  */

				connect(action, SIGNAL(triggered()), this, _slot);
			}

			colorMenu->addAction(action);

			if (colors.at(i) == _defaultColor) {

				colorMenu->setDefaultAction(action);
			}
		}
	}

	return colorMenu;
}

QIcon GraphFrame::create_ColorToolButtonIcon(const QString &_imageFile, QColor _color) {

	QPixmap pixmap(50, 80); 
	        pixmap.fill(Qt::transparent);
	

	QPainter painter(&pixmap); {

	//	QPixmap image(_imageFile); {

			QRect target(4, 0, 42, 43);
			QRect source(0, 0, 42, 43);

			painter.fillRect(QRect(0, 60, 50, 80), _color);
			painter.drawPixmap(target, QPixmap(_imageFile), source);
		}
	//}
	// Draw icon centered horizontally on button.

	return QIcon(pixmap);
}

QIcon GraphFrame::create_ColorIcon(QColor _color) {

	QPixmap pixmap(20, 20);
	QPainter painter(&pixmap); {

		painter.setPen(Qt::NoPen);
		painter.fillRect(QRect(0, 0, 20, 20), _color);
	}

	return QIcon(pixmap);
}

/* ------------------------------------------ (ACTIONS) */

QAction* GraphFrame::action_Exit() {

	if (!exitAction_) {

		exitAction_ = new QAction(tr("E&xit"), this); {

			exitAction_->setShortcuts(QKeySequence::Quit);
			exitAction_->setStatusTip(tr("Quit SceneGraph example"));

			/* ------------------------------------------ CONNECT: Exit the application */

			connect(exitAction_, SIGNAL(triggered()), this, SLOT(close()));
		}
	}

	return exitAction_;
}

QAction* GraphFrame::action_ItemDelete() {

	if (!deleteAction_) {

		deleteAction_ = new QAction(QIcon(imagePath + "delete.png"), tr("&Delete"), this); {

			deleteAction_->setShortcut(tr("Delete"));
			deleteAction_->setStatusTip(tr("Delete item from Graph"));

			/* ------------------------------------------ CONNECT: Delete the selected item */

			connect(deleteAction_, &QAction::triggered, [=] () {

				foreach(QGraphicsItem *item, scene_->selectedItems()) {

					if (item->type() == GraphEdge::Type) {

						scene_->removeItem(item);

						GraphEdge *edge(qgraphicsitem_cast<GraphEdge *>(item)); {

							edge->startItem_->removeEdge(edge);
							edge->endItem_->removeEdge(edge);
						}

						delete item;
					}
				}

				foreach(QGraphicsItem *item, scene_->selectedItems()) {

					if (item->type() == GraphVertex::Type) {

						qgraphicsitem_cast<GraphVertex *>(item)->removeEdges();
					}

					scene_->removeItem(item);

					delete item;
				}
			});
		}
	}

	return deleteAction_;
}

QAction* GraphFrame::action_ItemToFront() {

	if (!sendForwardAction_) {

		sendForwardAction_ = new QAction(QIcon(imagePath + "bringtofront.png"), tr("Bring to &Front"), this); {

			sendForwardAction_->setShortcut(tr("Ctrl+F"));
			sendForwardAction_->setStatusTip(tr("Bring item to front"));

			/* ------------------------------------------ (CONNECT) */

			connect(sendForwardAction_, &QAction::triggered, [=] () {

				if (scene_->selectedItems().isEmpty()) {

					return;
				}

				QGraphicsItem *selectedItem(scene_->selectedItems().first());

				QList<QGraphicsItem *> overlapItems(selectedItem->collidingItems());

				qreal zValue(0);

				foreach(QGraphicsItem *item, overlapItems) {

					if (item->zValue() >= zValue &&
						item->type() == GraphVertex::Type) {

						zValue = item->zValue() + 0.1;
					}
				}

				selectedItem->setZValue(zValue);

			});
		}
	}

	return sendForwardAction_;
}

QAction* GraphFrame::action_ItemToBack() {

	if (!sendBackAction_) {

		sendBackAction_ = new QAction(tr("Send to &Back"), this); {

			sendBackAction_->setShortcut(tr("Ctrl+T"));
			sendBackAction_->setIcon(QIcon(imagePath + "sendtoback.png"));
			sendBackAction_->setStatusTip(tr("Send item to back"));

			/* ------------------------------------------ (CONNECT) */

			connect(sendBackAction_, &QAction::triggered, [=] () {

				if (scene_->selectedItems().isEmpty()) {

					return;
				}

				QGraphicsItem *selectedItem(scene_->selectedItems().first());

				QList<QGraphicsItem *> overlapItems(selectedItem->collidingItems());

				qreal zValue(0);

				foreach(QGraphicsItem *item, overlapItems) {

					if (item->zValue() <= zValue /*&& item->type() == GraphItem::Type*/) {

						zValue = item->zValue() - 0.1;
					}
				}

				selectedItem->setZValue(zValue);

			});
		}
	}

	return sendBackAction_;
}


QAction* GraphFrame::action_TextBold() {

	if (!boldAction_) {

		boldAction_ = new QAction(tr("Bold"), this); {

			boldAction_->setShortcut(tr("Ctrl+B"));
			boldAction_->setIcon(QIcon(imagePath + "bold.png"));
			boldAction_->setCheckable(true);

			/* ------------------------------------------ (CONNECT) */

			connect(boldAction_, &QAction::triggered, [=] () {

				slot_HandleFontChange();

			});
		}
	}

	return boldAction_;
}

QAction* GraphFrame::action_TextUnderline() {

	if (!underlineAction_) {

		underlineAction_ = new QAction(tr("Underline"), this); {

			underlineAction_->setShortcut(tr("Ctrl+U"));
			underlineAction_->setIcon(QIcon(imagePath + "underline.png"));
			underlineAction_->setCheckable(true);

			/* ------------------------------------------ (CONNECT) */
			connect(underlineAction_, SIGNAL(triggered()), this, SLOT(slot_HandleFontChange()));
		}
	}

	return underlineAction_;
}

QAction* GraphFrame::action_TextItalic() {

	if (!italicAction_) {

		italicAction_ = new QAction(tr("Italic"), this); {

			italicAction_->setShortcut(tr("Ctrl+I"));
			italicAction_->setIcon(QIcon(imagePath + "italic.png"));
			italicAction_->setCheckable(true);

			/* ------------------------------------------ (CONNECT) */
			connect(italicAction_, SIGNAL(triggered()), this, SLOT(slot_HandleFontChange()));
		}
	}

	return italicAction_;
}

QAction* GraphFrame::action_ZoomReset() {

	if (!zoomResetAction_) {

		zoomResetAction_ = new QAction("&Zoom Reset", this); {
			/* ------------------------------------------ (CONNECT) */
			connect(zoomResetAction_, &QAction::triggered, [=] () {

				zoomSlider_->setValue(250);
				build_Matrix();
				view_->ensureVisible(QRectF(0, 0, 0, 0));

				set_ResetActionEnabled(false);
			});

			set_ResetActionEnabled(false);
		}
	}

	return zoomResetAction_;
}

QAction* GraphFrame::action_ZoomIn(int _level) {

	if (!zoomInAction_) {

		zoomInAction_ = new QAction("&Zoom In", this); {
			/* ------------------------------------------ (CONNECT) */
			connect(zoomInAction_, &QAction::triggered, [=] () {

				zoomSlider_->setValue(zoomSlider_->value() + _level);
			});
		}
	}

	return zoomInAction_;
}

QAction* GraphFrame::action_ZoomOut(int _level) {

	if (!zoomOutAction_) {

		zoomOutAction_ = new QAction("&Zoom Out", this); {
			/* ------------------------------------------ (CONNECT) */
			connect(zoomOutAction_, &QAction::triggered, [=] () {

				zoomSlider_->setValue(zoomSlider_->value() - _level);
			});
		}
	}

	return zoomOutAction_;
}



















//class DialogOptionsWidget : public QGroupBox {
//
//public:
//
//    explicit DialogOptionsWidget(QWidget *parent = 0);
//    void addCheckBox(const QString &text, int value);
//    void addSpacer();
//    int value() const;
//
//private:
//    typedef QPair<QCheckBox *, int> CheckBoxEntry;
//    QVBoxLayout *layout;
//    QList<CheckBoxEntry> checkBoxEntries;
//};
//
//DialogOptionsWidget::DialogOptionsWidget(QWidget *parent) : QGroupBox(parent), layout(new QVBoxLayout) {
//    //setTitle(Dialog::tr("Options"));
//    setLayout(layout);
//}
//
//void DialogOptionsWidget::addCheckBox(const QString &text, int value) {
//    QCheckBox *checkBox = new QCheckBox(text);
//    layout->addWidget(checkBox);
//    checkBoxEntries.append(CheckBoxEntry(checkBox, value));
//}
//
//void DialogOptionsWidget::addSpacer() {
//    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
//}
//
//int DialogOptionsWidget::value() const {
//    int result = 0;
//    foreach(const CheckBoxEntry &checkboxEntry, checkBoxEntries)
//        if (checkboxEntry.first->isChecked())
//            result |= checkboxEntry.second;
//    return result;
//}
//





//void GraphFrame::setColor() {
//
//    const QColorDialog::ColorDialogOptions options = QFlag(colorDialogOptionsWidget->value());
//    const QColor color = QColorDialog::getColor(Qt::green, this, "Select Color", options);
//
//    if (color.isValid()) {
//        colorLabel->setText(color.name());
//        colorLabel->setPalette(QPalette(color));
//        colorLabel->setAutoFillBackground(true);
//    }
//}










//   colorLabel = new QLabel; {

// colorLabel->setFrameStyle(frameStyle);
//    QPushButton *colorButton = new QPushButton(tr("QColorDialog::get&Color()"));

//  connect(colorButton, &QAbstractButton::clicked, this, &GraphFrame::setColor);

//   colorDialogOptionsWidget = new DialogOptionsWidget;
//  colorDialogOptionsWidget->addCheckBox(doNotUseNativeDialog, QColorDialog::DontUseNativeDialog);
//   colorDialogOptionsWidget->addCheckBox(tr("Show alpha channel"), QColorDialog::ShowAlphaChannel);
//   colorDialogOptionsWidget->addCheckBox(tr("No buttons"), QColorDialog::NoButtons);
//   layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 1, 0);
//  layout->addWidget(colorDialogOptionsWidget, 2, 0, 1, 2);

//     toolbox->addItem(page, tr("Color Dialog"));
//   layout->addWidget(colorButton);
//   layout->addWidget(colorLabel);