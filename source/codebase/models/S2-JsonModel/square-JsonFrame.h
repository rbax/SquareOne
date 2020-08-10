#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QUrl>

class QTextEdit;
class QTreeView;
class QTabWidget;
class QAction;
class QNetworkReply;
class QLineEdit;

#include "square-JsonModel.h"
#include "square-FrameInterface.h"

#include "S2-JsonModel_Export.h"


class S2_JSONMODEL_EXPORT JsonFrame : public FrameInterface {

    Q_INTERFACES(FrameInterface)

    Q_OBJECT

public: /* ---------------------------------------------------------- [PUBLIC] */

    explicit JsonFrame(QWidget *parent = 0);

    QAction* getAction_OpenFile();
    QAction* getAction_TreeIn();
    QAction* getAction_TreeOut();
    QAction* getAction_NetPost();
    QAction* getAction_NetGet();

    public slots:
    void update_Actions();

    private slots :
    void httpFinished();


private: /* --------------------------------------------------------- [PRIVATE] */

    QJsonDocument document_;
    JsonModel *model_;

    QTreeView *treeView_;
    QTextEdit *textEdit_;
    QTextEdit *output_;

    QAction *action_FileOpen_ = 0;
    QAction *action_FileClose_ = 0;
    QAction *action_Refresh_ = 0;
    QAction *action_RefreshOutput = 0;
    QAction *action_NetPost_ = 0;
    QAction *action_NetGet_ = 0;


    QLineEdit *urlLineEdit_;
    QTextEdit *responseTextEdit_;

    QUrl url_;
    QNetworkReply *reply_;
    QNetworkAccessManager manager_;

};
