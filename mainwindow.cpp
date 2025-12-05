#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Круги на форме");
    resize(800, 600);
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
    painter.setPen(Qt::black);
    painter.setBrush(Qt::blue);

    painter.drawEllipse(x_ - radius_, y_ - radius_, 2 * radius_, 2 * radius_);
}

void CircleContainer::~CircleContainer() {
    for (auto circle : circles_) {
        delete circle;
    }
    circles_.clear();
}

void CircleContainer::addCircle(CCircle *circle) {
    if (circle) {
        circles_.push_back(circle);
    }
}

CCircle* CircleContainer::getCircle(int index) const {
    if (index >= 0 && index < circles_.size()) {
        return circles_[index];
    }
    return nullptr;
}

int CircleContainer::count() const {
    return circles_.size();
}


