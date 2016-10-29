#ifndef BACKFIRE_H
#define BACKFIRE_H
/************************************/
/*            模拟退火法            */
/************************************/
#include "tsp.h"

const double INIT_TEMP = 1000 ;//系统初始温度
const double MIN_TEMP = 0.001 ;//系统最低温度
const double COOLINGRATE = 0.98 ;//冷却速度

// P( k ) = 1 / ( 1 + e ( - delta(Ek) / T ) )
class Backfire : public TSP {
public :
    Backfire() ;
    double update(vector<int> &path) ;
    void getNextState ( vector <int>& state ) ;
private :
    int citySize ;
    int MarkovChain ; // Markov链
    double temp ;	//系统当前温度
    double minTemp ;	//温度的下限，若温度T达到minTemp，则停止搜索
    double coolingRate ;	//冷却速度
    vector <int> curState ;	//当前状态
    vector <int> nextState ;//移动后状态
    vector <int> bestState ;//最好状态
} ;

#endif // BACKFIRE_H
