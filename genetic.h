#ifndef GENETIC_H
#define GENETIC_H

#include "tsp.h"

#define MUTANT_RATE 0.9
//Rate of mutation
#define POPULATION 100
//Population numbers of one generation
#define THRESHOLD 5
//If the elite's fitness stop incresing for how many generation the iteration stops
#define RAND_SEED 233
//Random seed
#define MAX_GENE 10
//Maxium number of generations
#define LARGE_POPULATION false
//If the population is large, which will decide whether using fitness
//or fitness ^ 2 as the value for each individual in the selection.
#define MAX_INT 2147483647

class Genetic : public TSP{
public:
    Genetic();
    vector<vector<int>> init(int numberOfCitis);
    int eval(const vector<int> &gene);
    void mutation(vector<vector<int>> &group, int cityNumber);
    vector<vector<int>> crossOver(const vector<vector<int>> lastGeneration, int cityNumber);
    void run();
};

#endif // GENETIC_H
