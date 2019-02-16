//
// Created by MandicFilip on 13.1.19..
//

#ifndef TSPOPTIMIZATION_COSTFUNCTION_H
#define TSPOPTIMIZATION_COSTFUNCTION_H


#include <vector>
#include "DataSet.h"

class CostFunction {
    std::vector<DataSet::DataElement> data;

protected:
    double getSingleDistance(DataSet::DataElement& p, DataSet::DataElement& q);

public:
    void setData(const std::vector<DataSet::DataElement> &dataSet);
    double getCompleteDistance(std::vector<int>& permutation);
};


#endif //TSPOPTIMIZATION_COSTFUNCTION_H
