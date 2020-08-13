#pragma once

// Includes: Qt
class QAction;
class QToolBox;
class QSpinBox;
class QComboBox;
class QFontComboBox;
class QButtonGroup;
class QLineEdit;
class QGraphicsTextItem;
class QFont;
class QToolButton;
class QAbstractButton;
class QGraphicsView;
class QSlider;
class QToolBar;
class QSplitter;
class QLabel;

// Includes: Square
#include "square-FrameInterface.h"

// Includes: Project
#include "S2-GraphModel_Export.h"
class DialogOptionsWidget;
class GraphScene;


class S2_GRAPHMODEL_EXPORT GraphFrame : public FrameInterface {

    Q_INTERFACES(FrameInterface)

        Q_OBJECT

        enum SelectionType { // finite list of possible selection states

        ITEM = 0, // selected a single item
        STACK = 1, // a stack of unrelated "single" items
        SET // a collection of items tied to a defined "item set"
    };

public: // ---------------------------------------------------------- PUBLIC

    GraphFrame();

    void set_ResetActionEnabled(bool);
    void build_Matrix();

    //void setColor();

    // - - - - - Actions

    QAction* action_Exit();

    QAction* action_ZoomReset();
    QAction* action_ZoomIn(int level);
    QAction* action_ZoomOut(int level);

    QAction* action_ItemDelete();
    QAction* action_ItemToFront();
    QAction* action_ItemToBack();

    QAction* action_TextBold();
    QAction* action_TextUnderline();
    QAction* action_TextItalic();


private slots: // --------------------------------------------------- PRIVATE SLOTS

    void slot_UpdateTextColor();
    void slot_UpdateItemColor();
    void slot_updateLineColor();

    void slot_TextButtonTriggered();
    void slot_FillButtonTriggered();
    void slot_LineButtonTriggered();

    void slot_HandleFontChange();

private: // --------------------------------------------------------- PRIVATE

    QToolBar* create_ModeToolBar();
    QToolBar* create_ColorToolBar();
    QToolBar* create_EditToolBar();
    QToolBar* create_TextToolBar();
    QToolBar* create_ZoomToolBar();

  //  QToolBar* create_ItemToolBar();

    QWidget* menu_ItemGUI();
    QWidget* menu_ItemData();

    QMenu* create_ColorMenu(const char* slot, QColor defaultColor);

    QIcon create_ColorToolButtonIcon(const QString& image, QColor color);
    QIcon create_ColorIcon(QColor color);

    QSlider* zoomSlider_;
    GraphScene* scene_;
    QGraphicsView* view_;

    // - - - - - Actions

    QAction* zoomResetAction_ = 0;
    QAction* zoomInAction_ = 0;
    QAction* zoomOutAction_ = 0;

    QAction* exitAction_ = 0;
    QAction* addAction_ = 0;
    QAction* deleteAction_ = 0;

    QAction* sendForwardAction_ = 0;
    QAction* sendBackAction_ = 0;
    QAction* aboutAction_ = 0;

    QAction* boldAction_ = 0;
    QAction* underlineAction_ = 0;
    QAction* italicAction_ = 0;

    QAction* textAction_ = 0;
    QAction* fillAction_ = 0;
    QAction* lineAction_ = 0;

    // - - - - - Item Collections

    QMenu* itemMenu_;

    QComboBox* fontSizeCombo_;
    QFontComboBox* fontCombo_;

    QButtonGroup* pointerModeGroup;
    QButtonGroup* backgroundButtonGroup;
    QButtonGroup* pointerTypeGroupbuttonGroup;

    QToolButton* fontColorButton_;
    QToolButton* fillColorButton_;
    QToolButton* lineColorButton_;
    QToolButton* pointerButton_;

    // - - - - - test item menus

    QLabel* colorLabel;
    DialogOptionsWidget* colorDialogOptionsWidget;
    QComboBox* item_TextSizeCombo_;
    QFontComboBox* item_TextFontCombo_;
    QSplitter* splitter_;
};
