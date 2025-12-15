#ifndef IMG_H
#define IMG_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QImage>
#include <QLabel>
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

private:
    QWidget *central;
    QMenu *fileMenu;
    QToolBar *fileTool;
    QImage img;
    QString filename;
    QLabel *imgWin;
    QAction *openFileAction;
    QAction *exitAction;

};
#endif // IMG_H
