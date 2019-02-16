//
// Created by MandicFilip on 13.1.19..
//

#include <iostream>
#include <vector>
#include <bits/ios_base.h>
#include <fstream>
#include <algorithm>
#include <random>
#include "../headers/GeneticAlgorithm.h"
#include "../headers/DataSet.h"
#include "../headers/CostFunction.h"
#include "../headers/RandomSearch.h"

void doGenetic(char* inputFile, char* outputFile, int numberOfRuns, GeneticAlgorithm::AlgorithmParameters parameters)
{
    DataSet* dataSet = new DataSet[numberOfRuns];
    CostFunction costFunction;
    GeneticAlgorithm* ga = new GeneticAlgorithm[numberOfRuns];

    for (int i = 0; i < numberOfRuns; ++i)
    {
        int isFileRead = dataSet[i].createDataSet(inputFile, 2);

        if (isFileRead == -1)
        {
            std::cout << "Can't open input file!" << std::endl;
            delete [] ga;
            delete [] dataSet;
            return;
        }

        costFunction.setData(dataSet[i].getData());
        ga[i].optimize(&dataSet[i], costFunction, parameters);
    }
    int bestRun;
    double bestValue = std::numeric_limits<double>::max();
    for (int i = 0; i < numberOfRuns; ++i)
    {
        if (dataSet[i].getBestResult() < bestValue)
        {
            bestRun = i;
        }
    }

    dataSet[bestRun].printBestResult(outputFile);

    delete [] ga;
    delete [] dataSet;

}

void randomSearch(char* inputFile, char* outputFile, int numberOfRuns)
{
    DataSet* dataSet = new DataSet[numberOfRuns];
    CostFunction costFunction;
    RandomSearch randomSearch;

    for (int i = 0; i < numberOfRuns; ++i)
    {
        dataSet[i].createDataSet(inputFile, 2);
        costFunction.setData(dataSet[i].getData());
        randomSearch.optimize(dataSet, 30000, costFunction);
    }
    delete [] dataSet;
}

int main(int argc, char** argv) {

    //basic args: input file, output file and number of runs
    //optional parameters: population size, mutation factor, selection limit, number of generations
    if (argc != 4 && argc != 8)
    {
        std::cout << "Wrong number of arguments! Should pass input and output files!";
        exit(1);
    }

    GeneticAlgorithm::AlgorithmParameters parameters;

    char* inputFile = argv[1];
    char* outputFile = argv[2];
    int numberOfRuns = atoi(argv[3]);

    if (argc > 4)       //passed parameters
    {
        parameters.populationSize = atoi(argv[4]);
        parameters.mutationFactor = atoi(argv[5]);
        parameters.selectionLimit = atoi(argv[6]);
        parameters.generationsNumber = atoi(argv[7]);
    }
    else                //default parameters
    {
        parameters.populationSize = 40000;
        parameters.mutationFactor = 0.0001;
        parameters.selectionLimit = 8000;
        parameters.generationsNumber = 800;
    }

    doGenetic(inputFile, outputFile, numberOfRuns, parameters);

    randomSearch(inputFile, outputFile, numberOfRuns);

    return 0;
}