#include "img.h"
#include <QHBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QDebug>

IMG::IMG(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle (QStringLiteral("影像處理"));
    central =new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout (central);
        imgWin = new QLabel();
    QPixmap *initPixmap = new QPixmap(300,200);
        gWin = new GTransform();
    initPixmap->fill (QColor (255, 255, 200));
    imgWin->resize (300,200);
    imgWin->setScaledContents(true);
    imgWin->setPixmap (*initPixmap);
    mainLayout->addWidget (imgWin);
    setCentralWidget (central);
    createActions();
    createMenus();
    createToolBars();
}

IMG::~IMG() {}
void IMG::createActions ()
{
    openFileAction = new QAction (QStringLiteral("開啟檔案&O"),this);
    openFileAction->setShortcut (tr("Ctrl+O"));
    openFileAction->setStatusTip (QStringLiteral("開啟影像檔案"));
    connect (openFileAction, SIGNAL (triggered()), this, SLOT (showOpenFile()));

    exitAction = new QAction (QStringLiteral("結束&Q"),this);
    exitAction->setShortcut (tr("Ctrl+Q"));
    exitAction->setStatusTip (QStringLiteral("退出程式"));
    connect (exitAction, SIGNAL(triggered()), this, SLOT (close()));

    geometryAction = new QAction (QStringLiteral("幾何轉換"),this);
    geometryAction->setShortcut (tr("Ctrl+G"));
    geometryAction->setStatusTip (QStringLiteral("影像幾何轉換"));
    connect (geometryAction, SIGNAL (triggered()),this, SLOT (showGeometryTransform()));
    connect (exitAction, SIGNAL (triggered()),gWin, SLOT (close()));

    enlargeAction = new QAction (QStringLiteral("放大&+"),this);
    enlargeAction->setShortcut (tr("Ctrl++"));
    enlargeAction->setStatusTip (QStringLiteral("放大影像"));
    connect (enlargeAction, SIGNAL (triggered()), this, SLOT (getenlarge()));
    zoomoutAction = new QAction (QStringLiteral("縮小&-"),this);

    zoomoutAction->setShortcut (tr("Ctrl+-"));
    zoomoutAction->setStatusTip (QStringLiteral("縮小檔案"));
    connect (zoomoutAction, SIGNAL(triggered()), this, SLOT (getZoomOut()));
}
void IMG::createMenus()
{
    fileMenu =menuBar ()->addMenu (QStringLiteral("檔案&F"));
    fileMenu->addAction (openFileAction);
    fileMenu->addAction(exitAction);
    fileMenu->addAction(geometryAction);
    toolMenu =menuBar ()->addMenu (QStringLiteral("工具&T"));
    toolMenu->addAction (enlargeAction);
    toolMenu->addAction(zoomoutAction);
}
void IMG::createToolBars ()
{
    fileTool =addToolBar("file");
    fileTool->addAction (openFileAction);
    fileTool =addToolBar("file");
    fileTool->addAction (enlargeAction);
    fileTool =addToolBar("file");
    fileTool->addAction (zoomoutAction);
    fileTool =addToolBar("file");
    fileTool->addAction(geometryAction);
}
void IMG::loadFile(QString filename)
{
    qDebug() <<QString("file name: %1").arg(filename);
    QByteArray ba=filename.toLatin1();
    printf("FN:%s\n", (char *) ba.data());
    img.load(filename);
    imgWin->setPixmap (QPixmap:: fromImage(img));
}
void IMG::showOpenFile()
{
    filename= QFileDialog::getOpenFileName (this,
                                            QStringLiteral("開啟影像"),
                                            tr("."),
                                            "bmp(*.bmp);;png(*.png)"
                                            ";;Jpeg(*.jpg)");
    if (!filename.isEmpty())
    {
        if (img.isNull())
        {
            loadFile(filename);
        }
        else
        {
            IMG *newIPWin = new IMG();
            newIPWin->show();
            newIPWin->loadFile(filename);
        }
    }
}


void IMG::getenlarge()
{
    if (img.isNull()) return;
    IMG *zoomWin = new IMG();
    zoomWin->show();
    QImage zoomImg = img.scaled(
        img.width() * 2.0,
        img.height() * 2.0,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
        );
    zoomWin->img = zoomImg;
    zoomWin->imgWin->setPixmap(QPixmap::fromImage(zoomImg));
}
void IMG::getZoomOut()
{
    if (img.isNull()) return;
    IMG *zoomWin = new IMG();
    zoomWin->show();
    QImage zoomImg = img.scaled(
        img.width() * 0.5,
        img.height() * 0.5,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
        );
    zoomWin->img = zoomImg;
    zoomWin->imgWin->setPixmap(QPixmap::fromImage(zoomImg));
}
void IMG::showGeometryTransform()
{
    if (!img.isNull())
        gWin->srcImg = img;
        gWin->inWin->setPixmap(QPixmap:: fromImage (gWin->srcImg));
        gWin->show();
}

