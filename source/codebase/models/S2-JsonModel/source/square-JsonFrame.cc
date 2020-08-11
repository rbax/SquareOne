/* |INCLUDES: QT| */
#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QAction>
#include <QTextEdit>
#include <QHeaderView>
#include <QTreeView>
#include <QToolBar>
#include <QRectF>
#include <QtWidgets>
#include <QtNetwork>
#include <QTextEdit>
#include <QJsonObject>
#include <QByteArray>
#include <QString>
#include <QSplitter>

/* |INCLUDES: SQUARE| */
#include "square.h"

/* |INCLUDES: PROJECT| */
#include "square-JsonFrame.h"
#include "square-JsonItem.h"
#include "square-JsonModel.h"


JsonFrame::JsonFrame(QWidget* _parent): FrameInterface() {

    QToolBar* toolBar(new QToolBar());
    toolBar->addAction(getAction_OpenFile());
    toolBar->addSeparator();
    toolBar->addAction(getAction_TreeIn());
    toolBar->addAction(getAction_TreeOut());
    toolBar->addSeparator();
    toolBar->addAction(getAction_NetGet());
    toolBar->addAction(getAction_NetPost());

    insert_Widget(toolBar, FrameInterface::HEADER);


// setStyleSheet("background-color:grey;");

//  insert_Widget(new QLabel("URL:"), FrameInterface::HEADER);

    insert_Widget(urlLineEdit_ = new QLineEdit(), FrameInterface::HEADER);
    urlLineEdit_->setText("http://requestb.in/1dfyg961");
    urlLineEdit_->setFocus();

    QString imagePath(SQUARE_IO::get_ImagePath(QString("S2-JsonModel")));

    /* ------------------------------------------ (JSONMODEL) */

    model_ = new JsonModel(QStringList() << "Variable" << "Value 1" << " Value 2" << "Value 3" << "Value 4" << "Value 5" << "Value 6" << "Value 7" << "Value 8" << "Value 9" << "Value 10", this);
    model_->setIcon(QJsonValue::Bool, QIcon(imagePath + "bullet_black.png"));
    model_->setIcon(QJsonValue::Double, QIcon(imagePath + "bullet_red.png"));
    model_->setIcon(QJsonValue::String, QIcon(imagePath + "bullet_blue.png"));
    model_->setIcon(QJsonValue::Array, QIcon(imagePath + "table.png"));
    model_->setIcon(QJsonValue::Object, QIcon(imagePath + "brick.png"));

/* ------------------------------------------ (TREE VIEW) */

    insert_Widget(treeView_ = new QTreeView(this), FrameInterface::BODY);
    treeView_->setModel(model_);
  //  treeView_->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    treeView_->header()->setSectionsMovable(true);
    treeView_->header()->setDefaultAlignment(Qt::AlignCenter);

    treeView_->setAlternatingRowColors(true);
    treeView_->setSelectionBehavior(QAbstractItemView::SelectItems);
    treeView_->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    treeView_->setAnimated(true);
    treeView_->setAllColumnsShowFocus(true);
    treeView_->setWordWrap(true);
    treeView_->setTextElideMode(Qt::ElideRight);

    treeView_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(treeView_->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection&,
            const QItemSelection&)),
            this, SLOT(update_Actions()));

/* ------------------------------------------ (TEXTEDIT: INPUT) */
    insert_Widget(textEdit_ = new QTextEdit(this), FrameInterface::FOOTER);
    textEdit_->setText(QString("{\"input\": {\"a\": [1, 2],\"b\" : [\"WEST\", \"EAST\", \"SOUTH\", \"NORTH\"], \"doeType\" : \"fullFactorial\"}} "));

/* ------------------------------------------ (TEXTEDIT: OUTPUT) */
    insert_Widget(output_ = new QTextEdit(this), FrameInterface::FOOTER);

    insert_Widget(responseTextEdit_ = new QTextEdit(this), FrameInterface::FOOTER);
    responseTextEdit_->setReadOnly(true);
    responseTextEdit_->setStyleSheet("background-color:white;");

}

QAction* JsonFrame::getAction_OpenFile() {

    if (!action_FileOpen_) {

        connect(action_FileOpen_ = new QAction("Load File ", this), &QAction::triggered, [=] () {
            QFile file(QFileDialog::getOpenFileName(this,
                                                    "Open JSON file",
                                                    SQUARE_IO::get_DataPath("S2-JsonModel"),
                                                    "JSON (*.json);; JSON (*.txt)"));

            if (file.open(QIODevice::ReadOnly)) {
                textEdit_->setPlainText(file.readAll());
                file.close();
                action_Refresh_->trigger();
            }
        });
    }

    return action_FileOpen_;
}


QAction* JsonFrame::getAction_TreeIn() {

    if (!action_Refresh_) {

        connect(action_Refresh_ = new QAction("Tree In", this), &QAction::triggered, [=] () {
            if (!model_->loadJson(textEdit_->toPlainText().toUtf8())) {
                QMessageBox::warning(this, "error", "Cannot load Json Data");
            }

            treeView_->expandAll();
            treeView_->resizeColumnToContents(0); // first column only
        });
    }

    return action_Refresh_;
}


QAction* JsonFrame::getAction_TreeOut() {

    if (!action_RefreshOutput) {
        connect(action_RefreshOutput = new QAction("Tree Out", this), &QAction::triggered, [=] () {
            output_->clear();
            output_->setPlainText(model_->get_Json());

        });
    }

    return action_RefreshOutput;
}


QAction* JsonFrame::getAction_NetPost() {

    if (!action_NetPost_) {

        connect(action_NetPost_ = new QAction("Post", this), &QAction::triggered, [=] () {
            responseTextEdit_->append("Post Request...");
            url_ = urlLineEdit_->text();

            QNetworkRequest request(url_);
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

            QByteArray byte_array;
            byte_array.append(output_->toPlainText());

            reply_ = manager_.post(request, byte_array);
            connect(reply_, SIGNAL(finished()), this, SLOT(httpFinished()));

            QEventLoop loop;
            connect(&manager_, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
            loop.exec();
        });
    }

    return action_NetPost_;
}


QAction* JsonFrame::getAction_NetGet() {

    if (!action_NetGet_) {

        connect(action_NetGet_ = new QAction("Get", this), &QAction::triggered, [=] () {
            responseTextEdit_->append("Get Request...");
            url_ = urlLineEdit_->text();
            reply_ = manager_.get(QNetworkRequest(url_));
            connect(reply_, SIGNAL(finished()), this, SLOT(httpFinished()));

            QEventLoop loop;
            connect(&manager_, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
            loop.exec();
        });
    }

    return action_NetGet_;
}



void JsonFrame::update_Actions() {

    bool hasSelection = !treeView_->selectionModel()->selection().isEmpty();
    /*action_RemoveRow_->setEnabled(hasSelection);
    action_RemoveColumn_->setEnabled(hasSelection);

    bool hasCurrent = treeView_->selectionModel()->currentIndex().isValid();
    action_InsertRow_->setEnabled(hasCurrent);
    action_InsertColumn_->setEnabled(hasCurrent);*/

    //if (hasCurrent) {
    //    treeView_->closePersistentEditor(treeView_->selectionModel()->currentIndex());
    //    int row = treeView_->selectionModel()->currentIndex().row();
    //    int column = treeView_->selectionModel()->currentIndex().column();
    //    if (treeView_->selectionModel()->currentIndex().parent().isValid()) {
    //    }
    //}
}


//connect(textEdit_, &QTextEdit::textChanged, [=] () {
//
//    if (model_->loadJson(textEdit_->toPlainText().toUtf8())) {
//
//        treeView_->expandAll();
//    }
//
//    else {
//
//        textEdit_->clear();
//        textEdit_->append("Error loading JSON Data");
//    }
//});


void JsonFrame::httpFinished() {

    QVariant redirectionTarget = reply_->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (reply_->error()) {

        QMessageBox::information(this, tr("HTTP"),
                                 tr("Download failed: %1.")
                                 .arg(reply_->errorString()));
    }
    else if (!redirectionTarget.isNull()) {
        QUrl newUrl = url_.resolved(redirectionTarget.toUrl());

        if (QMessageBox::question(this, tr("HTTP"),
            tr("Redirect to %1 ?").arg(newUrl.toString()),
            QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            url_ = newUrl;
            reply_->deleteLater();

            urlLineEdit_->clear();
            urlLineEdit_->setText(url_.toString());

            responseTextEdit_->append("");
            responseTextEdit_->append("redirect");
            responseTextEdit_->append("");
            responseTextEdit_->append("");
            return;
        }
    }
    else {
        responseTextEdit_->append("Reply:");
        responseTextEdit_->append(reply_->readAll());
    }
}
