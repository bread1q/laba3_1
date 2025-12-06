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

CCircle::CCircle(int x, int y) : x_(x), y_(y) {}

bool CCircle::contains(int x, int y) const {
    int dx = x - x_;
    int dy = y - y_;

    return (dx * dx + dy * dy) <= (radius_ * radius_);
}

void CCircle::draw(QPainter &painter) const {
    if (selected_) {
        painter.setPen(QPen(Qt::red, 2));
        painter.setBrush(QBrush(QColor(200, 200, 255, 150)));
    }
    else {
        painter.setPen(Qt::black);
        painter.setBrush(Qt::red);
    }

    painter.drawEllipse(x_ - radius_, y_ - radius_, 2 * radius_, 2 * radius_);
}

CircleContainer::~CircleContainer() {
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

void CircleContainer::clear() {
    for (auto circle : circles_) {
        delete circle;
    }
    circles_.clear();
}

void CircleContainer::removeSelected() {
    for (int i = circles_.size() - 1; i >= 0; i--) {
        if (circles_[i]->getSelected()) {
            delete circles_[i];
            circles_.erase(circles_.begin() + i);
        }
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

void CircleContainer::clearSelection() {
    for (auto circle : circles_) {
        circle->setSelected(false);
    }
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    for (int i = 0; i < container_.count(); i++) {
        CCircle* circle = container_.getCircle(i);
        if (circle) {
            circle->draw(painter);
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        int x = event->pos().x();
        int y = event->pos().y();

        bool clickedOnCircle = false;

        for (int i = 0; i < container_.count(); i++) {
            CCircle* circle = container_.getCircle(i);
            if (circle && circle->contains(x, y)) {
                clickedOnCircle = true;

                if (ctrlPressed_) {
                    circle->setSelected(!circle->getSelected());
                } else {
                    container_.clearSelection();
                    circle->setSelected(true);
                }
                break;
            }
        }

        if (!clickedOnCircle) {
            if (!ctrlPressed_) {
                container_.clearSelection();
            }
            CCircle* newCircle = new CCircle(x, y);
            if (!ctrlPressed_) {
                newCircle->setSelected(true);
            }
            container_.addCircle(newCircle);
        }

        update();
    }

    QMainWindow::mousePressEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Control) {
        ctrlPressed_ = true;
    }

    else if (event->key() == Qt::Key_Backspace) {
        container_.removeSelected();
        update();
    }

    QMainWindow::keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Control) {
        ctrlPressed_ = false;
    }
    QMainWindow::keyReleaseEvent(event);
}
