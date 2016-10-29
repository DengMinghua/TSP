#include "backfire.h"



Backfire::Backfire() {}

double Backfire::update(vector<int> &path)
{
    //随机初始化路径
    path.clear() ;
    int n = getCitySize();
    for ( int i = 0 ; i < n ; i ++ )
        path.push_back( i ) ;
    for ( int i = 0 ; i < n ; i ++ )
    {
        int x = rand() % n ;
        int y = rand() % n ;
        if ( x != y )
            swap ( path[x] , path[y] ) ;
    }
    //for ( int i = 0 ; i < path.size() ; i ++ )
    //	cout << path[i] << " " ;
    //cout << endl ;

    //初始化相关变量
    temp = INIT_TEMP ;//初始化当前温度最高
    minTemp = MIN_TEMP ;//初始化最低温度
    coolingRate = COOLINGRATE ;//初始化冷却速度
    citySize = getCitySize() ;//初始化城市个数------------------------我在TSP类里面增加一个函数
    MarkovChain = 10 * citySize ; //初始化Markov链
    curState = path ;//初始化当前路径
    bestState = path ;//初始化最好路径

    while( temp > minTemp )
    {
        for ( int i = 0 ; i < MarkovChain ; i ++ )
        {
            nextState = curState ;
            getNextState ( nextState ) ;//得到下一状态
            double deltaEk = get_path_length ( nextState ) - get_path_length ( curState ) ;
            if ( deltaEk <= 0 )                        //如果移动后得到更优解，则总是接受移动
            {
                curState = nextState ;
                if ( get_path_length ( bestState ) >= get_path_length ( curState ) ) //记录最好结果
                    bestState = curState ;

            }
            else //如果移动后没有得到更优解，则根据一定概率移动
            {
                if ( 1000.0 / ( 1.0 + exp( - deltaEk / temp ) ) < rand() % 1001 ) // P( k ) = 1 / ( 1 + e ( - delta(Ek) / T ) )
                {
                    curState = nextState ;              //接受的移动
                }
            }
        }
        temp *= coolingRate ;  //降温退火
    }
    path = bestState ;//最后设置最好状态
    return get_path_length(bestState);
}

void Backfire::getNextState ( vector <int>& state )
{
    int i = rand() % citySize ;
    int j = rand() % citySize ;
    if ( i == j )
        return ;
    if ( i > j )
        swap ( i , j ) ;
    int choose = rand() % 3 ;
    if ( choose == 0 ) // 交换编号为i和j的城市
    {
        swap ( state[i] , state[j] ) ;
    }
    else if ( choose == 1 )// 编号为i和j的城市之间左移一位，第一位移到最后
    {
        int tmp = state[i] ;
        for ( int k = i ; k < j ; k ++ )
        {
            state[k] = state[k+1] ;
        }
        state[j] = tmp ;
    }
    else if ( choose == 2 ) // 编号为i和j的城市之间置逆
    {
        reverse ( state.begin() + i , state.begin() + j ) ;
    }
}
