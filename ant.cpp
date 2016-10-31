#include "ant.h"

Ant::Ant(){
	name = "Ant Group";
}

void Ant::run(){
	int n = get_city_size();
	const int m = 200; // # ant
	const double alpha = 1;// 信息素重要程度因子
	const double beta = 5;// 启发函数重要程度因子
	const double rho = 0.1;// 信息素挥发因子
	const double Q = 1;// 常系数
	// 启发函数
	vector<vector<double> > Eta(n, vector<double>(n));
	vector<vector<double> > delta(n, vector<double>(n));
	for (int i = 0;i < n;++i){
		for (int j = 0;j < n;++j){
			Eta[i][j] = 1.0 / get_dis(i, j);
			delta[i][j] = Q / get_dis(i, j);
		}
	}
	// 信息素矩阵
	vector<vector<double> > T(n, vector<double>(n, 1));
	vector<vector<int> > route(m, vector<int>(n));
	int *select = new int[n];
	double *right = new double[n];
    double bestDis = DBL_MAX;
    vector<int> bestPath;
    while (1){
		++iter_time;
		for (int a = 0;a < m;++a){
			for (int i = 0;i < n;++i)select[i] = i;
			int y = n;
			vector<int> &r = route[a];
            int st = select[rand() % y]; // 随机一个出发点
			r[0] = st;
			select[st] = select[--y];
            for (int c = 1;c < n;++c){
				// (T^alpha) * (Eta^beta)
				double su = 0;
				for  (int j = 0;j < y;++j){
					int to = select[j];
					double ri = pow(T[st][to], alpha) * pow(Eta[st][to], beta);
					su += ri;
					right[j] = su;
				}
				double v = (rand() * 1.0 /  RAND_MAX) * su;
				//轮盘赌
				int j;
				for (j = 0;j < y;++j){
                    double ri = right[j];
					if (v <= ri)break;
                }
				int to = select[j];
				st = to;
                select[j] = select[--y];
				r[c] = to;
			}
		}
		//信息素
		//挥发
		for (int i = 0;i < n;++i){
			for (int j = 0;j < n;++j){
				T[i][j] *= (1 - rho);
			}
		}
		//分布
		for (int a = 0;a < m;++a){
			vector<int> &r = route[a]; 
			double len = get_path_length(r);
            if (len < bestDis){
				bestDis = len;
				bestPath = r;
			}
			for (int c = 1;c < n;++c){
				int from = r[c - 1];
				int to = r[c];
				T[from][to] += delta[from][to];
				T[to][from] = T[from][to];
			}
			int from = r[r.size() - 1];
			int to = r[0];
			T[from][to] += delta[from][to];
			T[to][from] = T[from][to];
		}
		SetBestPath(bestPath);
	}
	delete []right;
	delete []select;
}
