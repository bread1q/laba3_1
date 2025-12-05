#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

CCircle::CCircle() : x_(x), y_(y) {}

bool CCircle::contains(int x, int y) const {
    int dx = x - x_;
    int dy = y - y_;

    return (dx * dx + dy * dy) <= (radius_ * radius_);
}

void CCircle::draw(QPainter &painter) const {
    if (selected_) {
        painter.setPen(QPen(Qt::red, 2));
        painter.setBrush(QBrush(QColor(255, 200, 200, 150))); // светло-красный
    }
    else {
        painter.setPen(QPen(Qt::blue, 1));
        painter.setBrush(QBrush(QColor(200, 200, 255, 150))); // светло-синий
    }

    painter.drawEllipse(x_ - radius_, y_ - radius_, 2 * radius_, 2 * radius_);
}
