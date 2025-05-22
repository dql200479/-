#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMessageBox>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    canvas = QImage(280, 280, QImage::Format_RGB32);
    canvas.fill(Qt::white);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        drawingPoints.append(lastPoint);
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        QPainter painter(&canvas);
        painter.setPen(QPen(Qt::black, 15, Qt::SolidLine, Qt::RoundCap));
        painter.drawLine(lastPoint, event->pos());
        lastPoint = event->pos();
        drawingPoints.append(lastPoint);
        update();
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(10, 10, canvas.scaled(280, 280));
}

void MainWindow::on_clearButton_clicked()
{
    canvas.fill(Qt::white);
    drawingPoints.clear();
    update();
    ui->resultLabel->setText("结果：");
}

QImage MainWindow::preprocessImage()
{
    // 转换为28x28灰度图
    QImage processed = canvas.scaled(28, 28, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
                           .convertToFormat(QImage::Format_Grayscale8);

    // 二值化处理（根据需求调整阈值）
    for (int y = 0; y < 28; ++y) {
        uchar *line = processed.scanLine(y);
        for (int x = 0; x < 28; ++x) {
            line[x] = (line[x] < 200) ? 0 : 255; // 反转颜色
        }
    }
    return processed;
}

void MainWindow::on_recognizeButton_clicked()
{
    QImage processed = preprocessImage();
    //int digit = predictDigit(processed); // 调用模型推理
    //ui->resultLabel->setText("结果：" + QString::number(digit));
}

/*// 模型推理函数（需替换为实际模型调用）
int MainWindow::predictDigit(const QImage &image)
{
    // 示例伪代码，实际需要：
    // 1. 将QImage转换为模型输入格式（如Tensor）
    // 2. 调用模型推理
    // 3. 返回预测结果

    // 此处返回随机数作为示例
    return QRandomGenerator::global()->bounded(10);
}*/
