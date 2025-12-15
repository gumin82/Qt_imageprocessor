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
    initPixmap->fill (QColor (255, 255, 255));
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
    openFileAction->setShortcut (tr("Ctrl+0"));
    openFileAction->setStatusTip (QStringLiteral("開啟影像檔案"));
    connect (openFileAction, SIGNAL (triggered()), this, SLOT (showOpenFile()));
    exitAction = new QAction (QStringLiteral("結束&Q"),this);
    exitAction->setShortcut (tr("Ctrl+Q"));
    exitAction->setStatusTip (QStringLiteral("退出程式"));
    connect (exitAction, SIGNAL(triggered()), this, SLOT (close()));
}
void IMG::createMenus()
{
    fileMenu =menuBar ()->addMenu (QStringLiteral("檔案&F"));
    fileMenu->addAction (openFileAction);
    fileMenu->addAction(exitAction);
}
void IMG::createToolBars ()
{
    fileTool =addToolBar("file");
    fileTool->addAction (openFileAction);
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
