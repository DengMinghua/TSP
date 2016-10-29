#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QTimer *timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter;
    painter.begin(this);
    double minX = INT_MAX;
    double minY = INT_MAX;
    double maxX = INT_MIN;
    double maxY = INT_MIN;
    for (int i : ppath){
        Point &p = ps[i];
        minX = min(minX, p.x);
        minY = min(minY, p.y);
        maxX = max(maxX, p.x);
        maxY = max(maxY, p.y);
    }
    double dx = maxX - minX;
    double dy = maxY - minY;
    double dz = max(dx, dy);
    double ratio = 600.0 / dz;
    QPen qpen(Qt::green, 8, Qt::SolidLine);
    painter.setPen(qpen);
    for (int i : ppath){
        Point &p = ps[i];
        painter.drawPoint((p.x - minX) * ratio + 50, (p.y - minY) * ratio + 50);
    }
    painter.end();
}
