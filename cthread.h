#ifndef CTHREAD_H
#define CTHREAD_H
#include <QThread>
#include "tsp.h"

class CThread : public QThread{
public:
    CThread();
    CThread(TSP *tsp);
    ~CThread();
    void run();
public:
    vector<int> path;
    double minDis;
private:
    TSP *tsp;
};

#endif // CTHREAD_H
