#ifndef GENETIC_H
#define GENETIC_H

#include "tsp.h"

#define MUTANT_RATE 0.01
//Rate of mutation
#define POPULATION 100
//Population numbers of one generation
#define THRESHOLD 5
//If the elite's fitness stop incresing for how many generation the iteration stops
#define RAND_SEED 233
//Random seed
#define MAX_GENE 10
//Maxium number of generations
#define LARGE_POPULATION true
//If the population is large, which will decide whether using fitness
//or fitness ^ 2 as the value for each individual in the selection.
#define MAX_INT 65535

class Genetic : public TSP{
public:
    Genetic();
    void run();
};

#endif // GENETIC_H
