//
// Created by MandicFilip on 13.1.19..
//

#ifndef TSPOPTIMIZATION_GENETICALGORITHM_H
#define TSPOPTIMIZATION_GENETICALGORITHM_H

#include "CostFunction.h"

using PopulationElement = std::pair<double, std::vector<int>*>;
using Population = std::vector<PopulationElement>;

class GeneticAlgorithm {

public:

    GeneticAlgorithm();

    struct AlgorithmParameters {
        int generationsNumber;
        int populationSize;
        int selectionLimit;
        double mutationFactor;

        AlgorithmParameters();
    };

    void optimize(DataSet* dataSet, CostFunction& costFunction,
            GeneticAlgorithm::AlgorithmParameters& parameters);

private:
    AlgorithmParameters parameters;
    CostFunction costFunction;
    DataSet* dataSet;
    Population population;

    int* reproductionFlags;

    void initAlgorithm();

    void selection();
    void reproduction();
    void mutation();

    void calcCostValue();

    void evaluateGeneration();

    void doSingleReproduction(int first, int second, int crossingPoints[], int index);

    void deallocMemory();
};


#endif //TSPOPTIMIZATION_GENETICALGORITHM_H
