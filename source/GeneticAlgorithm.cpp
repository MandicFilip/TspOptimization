#include <random>

//
// Created by MandicFilip on 13.1.19..
//

#include <algorithm>
#include <random>
#include <iostream>
#include "../headers/GeneticAlgorithm.h"

GeneticAlgorithm::AlgorithmParameters::AlgorithmParameters()
{

}

GeneticAlgorithm::GeneticAlgorithm()
{}

void
GeneticAlgorithm::optimize(DataSet* dataSet, CostFunction& costFunction,
        GeneticAlgorithm::AlgorithmParameters& parameters)
{
    this->parameters = parameters;
    this->costFunction = costFunction;
    this->dataSet = dataSet;

    initAlgorithm();
    calcCostValue();
    for (int i = 0; i < parameters.generationsNumber; ++i)
    {
        selection();
        reproduction();
        mutation();

        calcCostValue();
        evaluateGeneration();

        if (i % 25 == 0) std::cout << i << ": " << this->dataSet->getBestResult() << std::endl;
    }
    std::cout << "final: " << this->dataSet->getBestResult() << std::endl;
    deallocMemory();
}

void GeneticAlgorithm::initAlgorithm()
{
    for (int i = 0; i < parameters.populationSize; ++i)
    {
        auto* vector = new std::vector<int>;
        for (int j = 0; j < dataSet->getPermutationSize(); ++j)
        {
            vector->push_back(j);
        }
        std::shuffle(vector->begin(), vector->end(), std::mt19937(std::random_device()()));

        population.push_back(PopulationElement(0, vector));
    }

    reproductionFlags = static_cast<int*>(malloc(dataSet->getPermutationSize() * sizeof(int)));
}

void GeneticAlgorithm::calcCostValue()
{
    for (int i = 0; i < parameters.populationSize; ++i)
    {
        population[i].first = costFunction.getCompleteDistance(*population[i].second);
    }
}

void GeneticAlgorithm::selection()
{
    std::sort(population.begin(), population.end(), [](PopulationElement a, PopulationElement b) -> int{
        return a.first < b.first;
    });
}

//elite approach !!!
void GeneticAlgorithm::reproduction()
{
    std::random_device rd;
    std::mt19937 rand(rd());
    std::uniform_int_distribution<int> random_int_limit(0, parameters.selectionLimit - 1);
    std::uniform_int_distribution<int> random_int_permutation(0, dataSet->getPermutationSize() - 1);

    for (int i = parameters.selectionLimit; i < parameters.populationSize; ++i)
    {
        int first = random_int_limit(rand);
        int second = random_int_limit(rand);

        int crossingPoints[] = {random_int_permutation(rand), random_int_permutation(rand)};
        while (crossingPoints[1] == crossingPoints[0])
        {
            crossingPoints[1] = random_int_permutation(rand);
        }
        if (crossingPoints[0] > crossingPoints[1])
        {
            std::swap(crossingPoints[0], crossingPoints[1]);
        }

        doSingleReproduction(first, second, crossingPoints, i);
    }
}

void GeneticAlgorithm::doSingleReproduction(int first, int second, int* crossingPoints, int index)
{
    for (int i = 0; i < dataSet->getPermutationSize(); ++i)
    {
        reproductionFlags[i] = 0;
    }


    int j = 0;
    for (int i = crossingPoints[0]; i <= crossingPoints[1]; ++i)
    {
        (*population[index].second)[j] = (*population[first].second)[i];
        reproductionFlags[(*population[first].second)[i]] = 1;
        j++;
    }

    int k = 0;
    while(j < dataSet->getPermutationSize())
    {
        if (!reproductionFlags[(*population[second].second)[k]])
        {
            (*population[index].second)[j] = (*population[second].second)[k];
            j++;
        }
        k++;
    }
}

void GeneticAlgorithm::mutation()
{
    std::random_device rd;
    std::mt19937 rand(rd());
    std::uniform_real_distribution<float > random_float(0, 1);
    std::uniform_int_distribution<int> random_int(0, dataSet->getPermutationSize() - 1);

    for (int i = 0; i < parameters.populationSize; ++i)
    {
        for (int j = 0; j < dataSet->getPermutationSize(); ++j)
        {
            if (random_float(rand) < parameters.mutationFactor) {
                int k = j;
                while (k == j)
                {
                    k = random_int(rand);
                }
                std::iter_swap(population[i].second->begin() + j, population[i].second->begin() + k);
            }
        }
    }

}

void GeneticAlgorithm::evaluateGeneration()
{
    auto best = std::min_element(population.begin(), population.end(),
            [](PopulationElement a, PopulationElement b) -> bool{
        return a.first < b.first;
    });
    dataSet->testBestResult(best->first, *best->second);
}

void GeneticAlgorithm::deallocMemory()
{
    for (auto& i : population)
    {
        if (i.second != nullptr)
            delete(i.second);
        i.second = nullptr;
    }

    free(reproductionFlags);
    reproductionFlags = nullptr;
}
