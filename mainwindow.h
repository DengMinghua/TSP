#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <map>
using namespace std;

#include <QMainWindow>
#include <QPen>
#include <QPainter>
#include "tsp.h"
#include "cthread.h"
#include "backfire.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void paintEvent(QPaintEvent *);
private:
    Ui::MainWindow *ui;
    vector<int> ppath;
    map<string, CThread> algos;
    vector<Point> ps;
};

#endif // MAINWINDOW_H
