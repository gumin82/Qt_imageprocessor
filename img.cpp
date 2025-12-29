#include "img.h"
#include <QHBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QDebug>
#include <QPainter>
#include <QInputDialog>

IMG::IMG(QWidget *parent)
    : MouseEvent(parent)
    , selecting(false)
{
    setWindowTitle(QStringLiteral("影像處理"));
    central = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout(central);
    imgWin = new QLabel();
    QPixmap *initPixmap = new QPixmap(300, 200);
    gWin = new GTransform();
    initPixmap->fill(QColor(255, 255, 200));
    imgWin->resize(300, 200);
    imgWin->setScaledContents(true);
    imgWin->setPixmap(*initPixmap);
    mainLayout->addWidget(imgWin);
    setCentralWidget(central);
    setMouseTracking(true);
    imgWin->setMouseTracking(true);
    statusLabel = new QLabel;
    statusLabel->setFixedWidth (100);
    MousePosLabel = new QLabel;
    MousePosLabel->setText(tr(" "));
    statusBar()->addPermanentWidget (MousePosLabel);

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
void IMG::mouseMoveEvent(QMouseEvent *event)
{
    QString str = "(" + QString::number (event->x()) + "," +
                  QString::number (event->y()) +")";
    
    // Get grayscale value at cursor position if image exists and cursor is within image bounds
    if (!img.isNull() && imgWin) {
        QPoint imgPos = imgWin->mapFrom(this, event->pos());
        QRect imgRect = imgWin->rect();
        
        if (imgRect.contains(imgPos)) {
            // Convert widget coordinates to image coordinates
            int imgX = (int)((double)imgPos.x() / imgWin->width() * img.width());
            int imgY = (int)((double)imgPos.y() / imgWin->height() * img.height());
            
            if (imgX >= 0 && imgX < img.width() && imgY >= 0 && imgY < img.height()) {
                QRgb pixel = img.pixel(imgX, imgY);
                // Calculate grayscale value using standard formula
                int gray = qGray(pixel);
                str += QString(" Gray: %1").arg(gray);
            }
        }
    }
    
    MousePosLabel->setText(str);
    
    // Update selection rectangle if selecting
    if (selecting) {
        selectionEnd = event->pos();
        update();  // Trigger repaint to show selection rectangle
    }
}
void IMG::mousePressEvent(QMouseEvent *event)
{
    QString str = "(" + QString::number (event->x()) + "," +
                  QString::number (event->y()) + ")";
    if (event->button() == Qt::LeftButton)
    {
        // Check if click is on the image
        if (!img.isNull() && imgWin) {
            QPoint imgPos = imgWin->mapFrom(this, event->pos());
            if (imgWin->rect().contains(imgPos)) {
                selecting = true;
                selectionStart = event->pos();
                selectionEnd = event->pos();
                statusBar()->showMessage(QStringLiteral("選取區域開始:") + str);
            }
        } else {
            statusBar()->showMessage (QStringLiteral("左鍵:") + str);
        }
    }
    else if (event->button() == Qt::RightButton)
    {
        statusBar()->showMessage (QStringLiteral("右鍵:") + str);
    }
    else if (event->button() == Qt::MiddleButton)
    {
        statusBar()->showMessage (QStringLiteral("中鍵:") + str);
    }
    qDebug() << "按壓";
}

void IMG::mouseReleaseEvent(QMouseEvent *event)
{
    QString str = "(" + QString::number (event->x()) + "," +
                  QString::number (event->y()) + ")";
    statusBar()->showMessage (QStringLiteral("釋放:") + str);
    qDebug() << "釋放";
    
    // If we were selecting, create zoom window with selected region
    if (selecting && event->button() == Qt::LeftButton) {
        selecting = false;
        
        // Calculate selection rectangle
        QRect selection(
            qMin(selectionStart.x(), selectionEnd.x()),
            qMin(selectionStart.y(), selectionEnd.y()),
            qAbs(selectionEnd.x() - selectionStart.x()),
            qAbs(selectionEnd.y() - selectionStart.y())
        );
        
        // Only proceed if selection has meaningful size
        if (selection.width() > 10 && selection.height() > 10 && !img.isNull()) {
            // Map selection to image coordinates
            QPoint imgStart = imgWin->mapFrom(this, selection.topLeft());
            QPoint imgEnd = imgWin->mapFrom(this, selection.bottomRight());
            
            // Convert widget coordinates to image pixel coordinates
            int x1 = (int)((double)imgStart.x() / imgWin->width() * img.width());
            int y1 = (int)((double)imgStart.y() / imgWin->height() * img.height());
            int x2 = (int)((double)imgEnd.x() / imgWin->width() * img.width());
            int y2 = (int)((double)imgEnd.y() / imgWin->height() * img.height());
            
            // Clamp to image bounds
            x1 = qMax(0, qMin(x1, img.width() - 1));
            y1 = qMax(0, qMin(y1, img.height() - 1));
            x2 = qMax(0, qMin(x2, img.width() - 1));
            y2 = qMax(0, qMin(y2, img.height() - 1));
            
            // Extract the selected region
            if (x2 > x1 && y2 > y1) {
                QImage selectedRegion = img.copy(x1, y1, x2 - x1, y2 - y1);
                
                // Ask user for zoom factor
                bool ok;
                double zoomFactor = QInputDialog::getDouble(
                    this,
                    QStringLiteral("選擇放大倍率"),
                    QStringLiteral("請輸入放大倍率:"),
                    2.0,  // default value
                    0.1,  // minimum
                    10.0, // maximum
                    1,    // decimals
                    &ok
                );
                
                if (ok) {
                    // Create and show zoom window
                    ZoomWindow *zoomWin = new ZoomWindow();
                    zoomWin->setImage(selectedRegion, zoomFactor);
                    zoomWin->show();
                }
            }
        }
        
        update();  // Clear the selection rectangle
    }
}

void IMG::mouseDoubleClickEvent(QMouseEvent *event)
{
    QString str = "(" + QString::number (event->x()) + "," +
                  QString::number (event->y()) + ")";
    statusBar()->showMessage (QStringLiteral("雙擊:") + str);
    qDebug() << "雙擊";
}

void IMG::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);
    
    // Draw selection rectangle if selecting
    if (selecting) {
        QPainter painter(this);
        painter.setPen(QPen(Qt::blue, 2, Qt::DashLine));
        
        QRect rect(
            qMin(selectionStart.x(), selectionEnd.x()),
            qMin(selectionStart.y(), selectionEnd.y()),
            qAbs(selectionEnd.x() - selectionStart.x()),
            qAbs(selectionEnd.y() - selectionStart.y())
        );
        
        painter.drawRect(rect);
    }
}

