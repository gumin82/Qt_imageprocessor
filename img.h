#ifndef IMG_H
#define IMG_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QImage>
#include <QLabel>
#include "gtransform.h"
class IMG : public QMainWindow
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

};
#endif // IMG_H
