#ifndef TSP_H
#define TSP_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
using namespace std;

struct Point{
    double x,y;
    Point(){}
    Point(double x, double y):x(x),y(y){}
};


void read_tsp(string filename, vector<Point> &ps);

class TSP{
public:
    //读取tsp文件，第一行为节点数
    //第二行开始，节点(ID+1), x, y
    //节点编号从0开始
    void read(string filename);
    //节点i到节点j的距离
    double get_dis(int i, int j);
    //计算路径总长度
    double get_path_length(const vector<int> &path);
    //保存路径
    void save(string filename, const vector<int> &path);
    // 返回城市数量
    int getCitySize();
    //设置最短路径path， 返回最短距离
    virtual double update(vector<int> &path);
public:
    vector<Point> ps;
private:
    vector<vector<double> > dis;
};


#endif // TSP_H
