//
// Created by MandicFilip on 23.1.19..
//

#ifndef TSPOPTIMIZATION_RANDOMSEARCH_H
#define TSPOPTIMIZATION_RANDOMSEARCH_H


#include "DataSet.h"
#include "CostFunction.h"

class RandomSearch
{
public:
    void optimize(DataSet* dataSet, int iterationsLimit, CostFunction& costFunction);
};


#endif //TSPOPTIMIZATION_RANDOMSEARCH_H
