#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

class CCircle
{

private:
    int x_;
    int y_;
    const int radius_ = 25;
    bool selected_ = false;

public:
    CCircle(int x, int y);

    void draw(QPainter &painter) const;
    bool contains(int x, int y) const;

    bool getSelected() { return selected_; }
    void setSelected(bool selected) { selected_ = selected; }
};

class CircleContainer
{

public:
    CircleContainer();

    void addCircle(CCircle* circle);

    CCircle* getCircle(int index) const;
    int count() const;

    void clear();

private:
    std::vector<CCircle*> circles_;
};
