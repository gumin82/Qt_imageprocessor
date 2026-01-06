#ifndef IMG_H
#define IMG_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QImage>
#include <QLabel>
#include <QPainter>
#include "gtransform.h"
#include "mouseevent.h"
#include "zoomwindow.h"
class IMG : public  MouseEvent
{
    Q_OBJECT

public:
    IMG(QWidget *parent = nullptr);
    ~IMG();
    void createActions();
    void createMenus();
    void createToolBars();
    void loadFile (QString filename);
private slots:
    void showOpenFile();
    void getZoomOut();
    void getenlarge();
    void showGeometryTransform();
   // void showMouseEvent();
protected:  // 確保這些事件方法在 IMG 中能夠被覆寫
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
private:
    QLabel *MousePosLabel;  // 在 IMG 類別中重新定義 MousePosLabel

private:
    GTransform  *gWin;
    QWidget *central;
    QMenu *fileMenu;
    QMenu *toolMenu;
    QToolBar *fileTool;
    QImage img;
    QString filename;
    QLabel *imgWin;
    QAction *openFileAction;
    QAction *exitAction;
    QAction *enlargeAction;
    QAction *zoomoutAction;
    QAction *geometryAction;
    double scaleFactor = 1.0;
    
    // Region selection variables
    bool selecting;
    QPoint selectionStart;
    QPoint selectionEnd;
    QRect selectionRect;

};
#endif // IMG_H
