#ifndef ZOOMWINDOW_H
#define ZOOMWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QImage>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QSpinBox>
#include <QColorDialog>

class ZoomWindow : public QMainWindow
{
    Q_OBJECT

public:
    ZoomWindow(QWidget *parent = nullptr);
    ~ZoomWindow();
    
    void setImage(const QImage &image, double zoomFactor = 2.0);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void saveImageAs();
    void setBrushSize(int size);
    void selectBrushColor();
    void toggleDrawMode();

private:
    void createActions();
    void createMenus();
    void createToolBars();

    QLabel *imageLabel;
    QImage originalImage;
    QImage editedImage;
    
    // Brush tool variables
    bool drawMode;
    QPoint lastDrawPoint;
    int brushSize;
    QColor brushColor;
    
    // Actions and UI elements
    QAction *saveAsAction;
    QAction *drawModeAction;
    QAction *colorAction;
    QMenu *fileMenu;
    QMenu *toolMenu;
    QToolBar *toolBar;
    QSpinBox *brushSizeSpinBox;
};

#endif // ZOOMWINDOW_H
