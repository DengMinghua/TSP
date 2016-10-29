#include "cthread.h"

CThread::CThread(){

}

CThread::CThread(TSP *tsp):tsp(tsp){

}

CThread::~CThread(){
}

void CThread::run(){
    while(1){
        minDis = tsp->update(path);
    }
}
