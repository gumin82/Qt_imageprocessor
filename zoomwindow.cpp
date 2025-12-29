#include "zoomwindow.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QStatusBar>

ZoomWindow::ZoomWindow(QWidget *parent)
    : QMainWindow(parent)
    , drawMode(false)
    , brushSize(5)
    , brushColor(Qt::red)
{
    setWindowTitle(QStringLiteral("放大視窗"));
    
    // Create central widget
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    
    imageLabel = new QLabel(this);
    imageLabel->setScaledContents(false);
    imageLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(imageLabel);
    
    setCentralWidget(centralWidget);
    
    createActions();
    createMenus();
    createToolBars();
    
    resize(800, 600);
}

ZoomWindow::~ZoomWindow()
{
}

void ZoomWindow::setImage(const QImage &image, double zoomFactor)
{
    originalImage = image;
    
    // Create zoomed image
    int newWidth = (int)(image.width() * zoomFactor);
    int newHeight = (int)(image.height() * zoomFactor);
    
    editedImage = image.scaled(newWidth, newHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imageLabel->setPixmap(QPixmap::fromImage(editedImage));
    imageLabel->resize(editedImage.size());
}

void ZoomWindow::createActions()
{
    saveAsAction = new QAction(QStringLiteral("另存新檔"), this);
    saveAsAction->setShortcut(tr("Ctrl+S"));
    saveAsAction->setStatusTip(QStringLiteral("儲存編輯後的影像"));
    connect(saveAsAction, &QAction::triggered, this, &ZoomWindow::saveImageAs);
    
    drawModeAction = new QAction(QStringLiteral("畫筆模式"), this);
    drawModeAction->setCheckable(true);
    drawModeAction->setStatusTip(QStringLiteral("啟用畫筆工具"));
    connect(drawModeAction, &QAction::triggered, this, &ZoomWindow::toggleDrawMode);
    
    colorAction = new QAction(QStringLiteral("選擇顏色"), this);
    colorAction->setStatusTip(QStringLiteral("選擇畫筆顏色"));
    connect(colorAction, &QAction::triggered, this, &ZoomWindow::selectBrushColor);
}

void ZoomWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(QStringLiteral("檔案(&F)"));
    fileMenu->addAction(saveAsAction);
    
    toolMenu = menuBar()->addMenu(QStringLiteral("工具(&T)"));
    toolMenu->addAction(drawModeAction);
    toolMenu->addAction(colorAction);
}

void ZoomWindow::createToolBars()
{
    toolBar = addToolBar(QStringLiteral("工具列"));
    toolBar->addAction(saveAsAction);
    toolBar->addAction(drawModeAction);
    toolBar->addAction(colorAction);
    
    // Add brush size control
    QLabel *brushLabel = new QLabel(QStringLiteral("  筆刷大小: "));
    toolBar->addWidget(brushLabel);
    
    brushSizeSpinBox = new QSpinBox(this);
    brushSizeSpinBox->setMinimum(1);
    brushSizeSpinBox->setMaximum(50);
    brushSizeSpinBox->setValue(brushSize);
    connect(brushSizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), 
            this, &ZoomWindow::setBrushSize);
    toolBar->addWidget(brushSizeSpinBox);
}

void ZoomWindow::saveImageAs()
{
    if (editedImage.isNull()) {
        QMessageBox::warning(this, QStringLiteral("錯誤"), 
                           QStringLiteral("沒有影像可以儲存"));
        return;
    }
    
    QString fileName = QFileDialog::getSaveFileName(
        this,
        QStringLiteral("另存影像"),
        "",
        QStringLiteral("PNG Image (*.png);;JPEG Image (*.jpg *.jpeg);;BMP Image (*.bmp)")
    );
    
    if (fileName.isEmpty())
        return;
    
    bool ok = editedImage.save(fileName);
    
    if (!ok) {
        QMessageBox::warning(this, QStringLiteral("錯誤"), 
                           QStringLiteral("存檔失敗"));
    } else {
        QMessageBox::information(this, QStringLiteral("成功"), 
                               QStringLiteral("檔案已儲存"));
    }
}

void ZoomWindow::setBrushSize(int size)
{
    brushSize = size;
}

void ZoomWindow::selectBrushColor()
{
    QColor color = QColorDialog::getColor(brushColor, this, QStringLiteral("選擇畫筆顏色"));
    if (color.isValid()) {
        brushColor = color;
    }
}

void ZoomWindow::toggleDrawMode()
{
    drawMode = drawModeAction->isChecked();
    if (drawMode) {
        setCursor(Qt::CrossCursor);
        statusBar()->showMessage(QStringLiteral("畫筆模式已啟用"));
    } else {
        setCursor(Qt::ArrowCursor);
        statusBar()->showMessage(QStringLiteral("畫筆模式已關閉"));
    }
}

void ZoomWindow::mousePressEvent(QMouseEvent *event)
{
    if (drawMode && event->button() == Qt::LeftButton) {
        // Map the click position to image coordinates
        QPoint clickPos = imageLabel->mapFrom(this, event->pos());
        if (imageLabel->rect().contains(clickPos)) {
            lastDrawPoint = clickPos;
        }
    }
}

void ZoomWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (drawMode && (event->buttons() & Qt::LeftButton)) {
        QPoint currentPos = imageLabel->mapFrom(this, event->pos());
        
        if (imageLabel->rect().contains(currentPos) && !lastDrawPoint.isNull()) {
            // Draw on the image
            QPainter painter(&editedImage);
            painter.setPen(QPen(brushColor, brushSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter.drawLine(lastDrawPoint, currentPos);
            
            // Update display
            imageLabel->setPixmap(QPixmap::fromImage(editedImage));
            
            lastDrawPoint = currentPos;
        }
    }
}

void ZoomWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (drawMode && event->button() == Qt::LeftButton) {
        lastDrawPoint = QPoint();
    }
}

void ZoomWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);
}
