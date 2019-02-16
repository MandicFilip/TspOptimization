//
// Created by MandicFilip on 23.1.19..
//

#include <algorithm>
#include <vector>
#include <random>
#include <iostream>
#include <iomanip>
#include "../headers/RandomSearch.h"

void RandomSearch::optimize(DataSet* dataSet, int iterationsLimit, CostFunction& costFunction)
{
    auto* vector = new std::vector<int>;
    for (int i = 0; i < dataSet->getPermutationSize(); ++i)
    {
        vector->push_back(i);
    }
    long double completeDistance = 0;
    for (int i = 0; i < iterationsLimit; ++i)
    {
        double distance = costFunction.getCompleteDistance(*vector);
        completeDistance += distance;
        std::shuffle(vector->begin(), vector->end(), std::mt19937(std::random_device()()));
    }

    if (iterationsLimit != 0)
        completeDistance = completeDistance / iterationsLimit;

    std::cout << std::fixed;
    std::cout << std::setprecision(3);
    std::cout << "Overall distance: " << completeDistance << std::endl;

    delete vector;
}
