#include "genetic.h"


Genetic::Genetic(){
    name = "Genetic Algorithm";
}

//Generate a initial group with the giving number of cities
vector<vector<int>> Genetic::init(int numberOfCitis) {
    vector<vector<int>> group;
    srand(RAND_SEED + time(nullptr));
    for (int i = 0; i < POPULATION; i++) {
        vector<int> gene;
        vector<bool> geneList;
        int pick;
        for (int j = 0; j < numberOfCitis; j++) geneList.push_back(true);
        for (int j = 0; j < numberOfCitis; j++) {
            while (!geneList[pick = rand() % numberOfCitis]) {
            }
            gene.push_back(pick);
            geneList[pick] = false;
        }
        group.push_back(gene);
    }
    return group;
}

// Eval an individual's fitness with the giving adjacent list(map)
int Genetic::eval(const vector<int> &gene) {
    int value = 0;
    for (int i = 0; i < gene.size(); i++)
        value += get_dis(gene[i],gene[(i + 1) % gene.size()]);
    return value;
}

// Using crossover to generate a new generation from last generation
vector<vector<int>> crossOver(const vector<vector<int>> & lastGeneration, int cityNumber) {
    vector<vector<int>> CurrentGeneration;
    vector<int> fitnessListOfCurrentGeneration;
    long fitnessSum = 0;
    int fitness = 0;
    int maxFitness = -1;
    int elite = -1;
    srand(RAND_SEED + time(nullptr));
    for (int i = 0; i < POPULATION; i++) {
        fitnessListOfCurrentGeneration.push_back(fitness = eval(lastGeneration[i]));
        if (LARGE_POPULATION)
        fitnessSum += fitness * fitness;
        else fitnessSum += fitness;
        if (fitness > maxFitness) {
            maxFitness = fitness;
            elite = i;
        }
    }
    cout << maxFitness << endl;
    for (int i = 0; i < POPULATION - 1; i++) {
        long pickFather = rand() % fitnessSum + 1;
        long pickMother = rand() % fitnessSum + 1;
        long partialSum = 0;
        int father = -1, mother = -1;
        for (int j = 0; j < POPULATION; j++) {
            if (LARGE_POPULATION)
            partialSum += fitnessListOfCurrentGeneration[j] * fitnessListOfCurrentGeneration[j];
            else
            partialSum += fitnessListOfCurrentGeneration[j];

            if (partialSum >= pickFather && father == -1)
                father = j;
            if (partialSum >= pickMother && mother == -1)
                mother = j;
        }
        vector<int> child;
        int pick = rand() % cityNumber;
        int nextpick = -1;
        vector<bool> picked(cityNumber, false);
        for (int i = 0; i < cityNumber; i++) {
            picked[pick] = true;
            child.push_back(pick);
            int min = MAX_INT;
            for (int j = 0; j < cityNumber; j++) {
                if (lastGeneration[father][j] == pick && get_dis(pick,lastGeneration[father][(j + 1) % cityNumber]) < min && !picked[lastGeneration[father][(j + 1) % cityNumber]]) {
                    min = get_dis(pick,lastGeneration[father][(j + 1) % cityNumber]);
                    nextpick = lastGeneration[father][(j + 1) % cityNumber];
                }
                if (lastGeneration[mother][j] == pick && get_dis(pick,lastGeneration[mother][(j + 1) % cityNumber]) < min && !picked[lastGeneration[mother][(j + 1) % cityNumber]]) {
                    min = get_dis(pick,lastGeneration[mother][(j + 1) % cityNumber]);
                    nextpick = lastGeneration[mother][(j + 1) % cityNumber];
                }
            }
            pick = nextpick;
        }
        CurrentGeneration.push_back(child);
    }
    CurrentGeneration.push_back(lastGeneration[elite]);
    return CurrentGeneration;
}

void Genetic::mutation(vector<vector<int>> &group, int cityNumber) {
    bool mutant = false;
    srand(RAND_SEED + time(nullptr));
    for (int i = 0; i < POPULATION - 1; i++) {
        mutant = (rand() % 10000) >= (MUTANT_RATE * 10000);
        if (mutant) {
            int mutantPos1 = rand() % cityNumber;
            int mutantPos2 = rand() % cityNumber;
            int temp = group[i][mutantPos1];
            group[i][mutantPos1] = group[i][mutantPos2];
            group[i][mutantPos2] = temp;
        }
    }
}

void Genetic::run(){
    int numberOfCities = get_city_size();
    auto initGroup = init(numberOfCities);
    int eliteFitness = -1;
    int lastEliteFitness = -1;
    int stopCnt = 0;
    for (int i = 0; i < MAX_GENE; i++) {
        lastEliteFitness = eliteFitness;
        initGroup = crossOver(initGroup, 4);
        eliteFitness = eval(initGroup[POPULATION - 1]);
        if (eliteFitness == lastEliteFitness) stopCnt++;
        else stopCnt = 0;
        if (stopCnt == THRESHOLD) break;
    }
    SetBestPath(initGroup[POPULATION -1]);
}
