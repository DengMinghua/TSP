#include "tsp.h"

void read_tsp(string filename, vector<Point> &ps){
    ps.clear();
    ifstream fin(filename.c_str());
    int n;
    int id;
    double x,y;
    fin >> n;
    for (int i = 0;i < n;++i){
        fin >> id >> x >> y;
        ps.push_back(Point(x,y));
    }
}

void TSP::read(string filename){
    read_tsp(filename, ps);
    int n = ps.size();
    dis = vector<vector<double> >(n, vector<double>(n, 0));
    for (int i = 0;i < n;++i){
        for (int j = i + 1;j < n;++j){
            double dx = ps[i].x - ps[j].x;
            double dy = ps[i].y - ps[j].y;
            double d = sqrt(dx*dx + dy*dy);
            dis[i][j] = d;
            dis[j][i] = d;
        }
    }
}

//节点i到节点j的距离
double TSP::get_dis(int i, int j){
    return dis[i][j];
}
//计算路径总长度
double TSP::get_path_length(const vector<int> &path){
    double s = 0;
    for (size_t i = 0;i < path.size() - 1;++i){
        s += dis[i][i + 1];
    }
    s += dis[path.size() - 1][0];
    return s;
}
//保存路径
void TSP::save(string filename, const vector<int> &path){
    ofstream fout(filename.c_str());
    for (size_t i = 0;i < path.size();++i){
        fout << path[i] << " ";
    }
    fout << endl;
    fout << "Cost: " << get_path_length(path) << endl;
}

int TSP::getCitySize(){
    return ps.size();
}
