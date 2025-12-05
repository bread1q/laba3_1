#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

class CCircle
{

private:
    int x_;
    int y_;
    const int radius = 25;
    bool selected;

public:
    CCircle();
    void draw(QPainter &painter) const;
    bool contains(int x, int y) const;
    bool isSelected();
};
