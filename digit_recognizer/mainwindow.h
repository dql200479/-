#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPoint>
#include <QPainter>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_clearButton_clicked();
    void on_recognizeButton_clicked();

private:
    Ui::MainWindow *ui;
    QImage canvas;
    QPoint lastPoint;
    QVector<QPoint> drawingPoints;

    QImage preprocessImage();
    int predictDigit(const QImage &image); // 需要集成模型推理
};

#endif // MAINWINDOW_H
