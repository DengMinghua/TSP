#include "genetic.h"
#include <assert.h>

Genetic::Genetic(){
    name = "Genetic Algorithm";
}

//Generate a initial group with the giving number of cities
vector<vector<int>> Genetic::init(int numberOfCities) {
    vector<vector<int>> group;
    srand(RAND_SEED + time(nullptr));
    for (int i = 0; i < POPULATION; i++) {
        vector<int> gene;
        vector<bool> geneList;
        int pick;
        for (int j = 0; j < numberOfCities; j++) geneList.push_back(true);

        for (int j = 0; j < numberOfCities; j++) {
            pick = rand() % numberOfCities;
            while (!geneList[pick]) {
                  pick = rand() % numberOfCities;
         }
            gene.push_back(pick);
            geneList[pick] = false;
        }
        group.push_back(gene);
        for (int i = 0; i < gene.size(); i++)
            cerr << gene[i] << " ";
        cerr << endl;
    }
    cerr << "finsihed" << endl;
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
vector<vector<int>> Genetic::crossOver(const vector<vector<int>> lastGeneration, int cityNumber) {
    //cout << "BeginB" << endl;
    vector<vector<int>> CurrentGeneration;
    vector<int> fitnessListOfCurrentGeneration;
    long fitnessSum = 0;
    int fitness = 0;
    int maxFitness = MAX_INT;
    int elite = -1;
    srand(RAND_SEED + time(nullptr));
    for (int i = 0; i < POPULATION; i++) {
        fitness = eval(lastGeneration[i]);
        fitnessListOfCurrentGeneration.push_back(fitness);
        //cerr << fitness << " ";
        fitnessSum += fitness;
        if (fitness < maxFitness) {
            maxFitness = fitness;
            elite = i;
        }
    }
    //cerr << endl;
    cout << fitnessSum / cityNumber << endl;
    for (int i = 0; i < POPULATION - 1; i++) {
        long pickFather = (rand()  * rand ()) % fitnessSum;
        long pickMother = (rand() * rand ()) % fitnessSum;
       //cout << pickFather << " " << pickMother << " " << fitnessSum << endl;
        long partialSum = 0;
        int father = -1, mother = -1;
        for (int j = 0; j < POPULATION; j++) {
            partialSum +=  fitnessListOfCurrentGeneration[j];

            if (partialSum >= pickFather && father == -1)
                father = j;
            if (partialSum >= pickMother && mother == -1)
                mother = j;
        }
        //cout << father << " " << mother << endl;
        vector<int> child;
        int pick = rand() % cityNumber;
        vector<bool> picked;
        for(int i = 0; i < cityNumber;i++) picked.push_back(false);
        for (int i = 0; i < cityNumber - 1; i++) {
            //cout << pick << " " << picked.size()<<endl;
            assert(pick < picked.size());
            picked[pick] = true;
            child.push_back(pick);
            int fatherPrev = -1;
            int motherPrev = -1;
            int fatherNext = -1;
            int motherNext = -1;
            for (int j = 0; j < cityNumber; j++) {
                if (lastGeneration[father][j] == pick){
                    for(fatherNext = j+1; picked[lastGeneration[father][fatherNext  % cityNumber]]; fatherNext ++){}
                    fatherPrev = j;
                }
                if (lastGeneration[mother][j] == pick){
                    for(motherNext = j+1; picked[lastGeneration[mother][motherNext  % cityNumber]]; motherNext ++){}
                    motherPrev = j;
                }
            }
            fatherNext %= cityNumber;
            motherNext %= cityNumber;
            if(get_dis(fatherPrev,fatherNext) < get_dis(motherPrev,motherNext))
            pick = lastGeneration[father][fatherNext];
            else pick = lastGeneration[mother][motherNext];
        }
        for(int i = 0; i < cityNumber;i++) if (!picked[i]) child.push_back(i);
//        for (int i = 0; i < child.size(); i++)
//            cerr << child[i] << " ";
//        cerr << endl;
        CurrentGeneration.push_back(child);
    }
    CurrentGeneration.push_back(lastGeneration[elite]);
    //cout << "finishedB" << endl;
    return CurrentGeneration;
}

void Genetic::mutation(vector<vector<int>> &group, int cityNumber) {
    bool mutant = false;
    srand(RAND_SEED + time(nullptr));
    for (int i = 0; i < POPULATION - 1; i++) {
        mutant = (rand() % 10000) <= (MUTANT_RATE * 10000);
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
    SetBestPath(initGroup[POPULATION -1]);
    int eliteFitness = -1;
    int lastEliteFitness = -1;
    int stopCnt = 0;
    while(1) {
        ++iter_time;
        lastEliteFitness = eliteFitness;
        initGroup = crossOver(initGroup, numberOfCities);
        mutation(initGroup,numberOfCities);
//        for (int i = 0; i < initGroup.size(); i++){
//            for (int j = 0;j < numberOfCities; j++)
//            cerr << initGroup[i][j] << " ";
//            cerr <<endl;
//        }
//        cerr << endl;
//        eliteFitness = eval(initGroup[POPULATION - 1]);
//        if (eliteFitness == lastEliteFitness) stopCnt++;
//        else stopCnt = 0;
//        if (stopCnt == THRESHOLD) break;
        SetBestPath(initGroup[POPULATION -1]);
    }
 SetBestPath(initGroup[POPULATION -1]);
}
