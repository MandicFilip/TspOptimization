//
// Created by MandicFilip on 13.1.19..
//

#include <cmath>
#include "../headers/CostFunction.h"

void CostFunction::setData(const std::vector<DataSet::DataElement>& dataSet)
{
    CostFunction::data = dataSet;
}

double CostFunction::getSingleDistance(DataSet::DataElement& p, DataSet::DataElement& q)
{
    return sqrt(pow(p.coordinates[0] - q.coordinates[0], 2) + pow(p.coordinates[1] - q.coordinates[1], 2));
}

double CostFunction::getCompleteDistance(std::vector<int>& permutation)
{
    if (permutation.size() != data.size()) return -1;

    double sum = 0;
    for (int i = 0; i < data.size() - 1; ++i)
    {
        sum += getSingleDistance(data[permutation[i]], data[permutation[i + 1]]);
    }

    return sum;
}
