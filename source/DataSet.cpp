//
// Created by MandicFilip on 13.1.19..
//

#include <fstream>
#include <iostream>
#include <iomanip>
#include "../headers/DataSet.h"
#include <limits>

int DataSet::createDataSet(std::string fileName, int dimension)
{
    std::ifstream file(fileName, std::ifstream::in);

    if (!file.is_open()) return -1;

    double tmp;

    permutationSize = 0;
    while(!file.eof())
    {
        DataElement element;
        file >> tmp;
        element.coordinates.push_back(tmp);

        if (file.eof()) break;

        for (int i = 1; i < dimension; ++i)
        {
            file >> tmp;
            element.coordinates.push_back(tmp);
        }

        data.push_back(element);
        permutationSize++;
    }
    file.close();

    for (int i = 0; i < permutationSize; ++i)
    {
        bestPermutation.push_back(i);
    }

    bestResult = std::numeric_limits<double>::max();

    this->dimension = dimension;

    return 0;
}

void DataSet::printBestResult(std::string fileName)
{
    std::ofstream file(fileName, std::ofstream::out);

    if (!file.is_open())
    {
        std::cout << "File can't open, best permutation can't be printed!" << std::endl;
        return;
    }


    file << "Best complete distance is: " << bestResult << std::endl;
    file << "Holes positions: " << std::endl;

    file.setf(std::ios::fixed, std::ios::floatfield);
    file.precision(3);
    for (int i = 0;  i != permutationSize; i++)
    {
        for (int j = 0; j < dimension - 1; ++j)
        {
            file << data[bestPermutation[i]].coordinates[j] << " ";
        }
        file << data[bestPermutation[i]].coordinates[dimension - 1] << std::endl;
    }

    file.close();
}

void DataSet::printJustHoles(std::string fileName)
{
    std::ofstream file(fileName, std::ofstream::out);

    if (!file.is_open())
    {
        std::cout << "File can't open, best permutation can't be printed!" << std::endl;
        return;
    }

    file.setf(std::ios::fixed, std::ios::floatfield);
    file.precision(3);
    for (int i = 0;  i != permutationSize; i++)
    {
        for (int j = 0; j < dimension - 1; ++j)
        {
            file << data[bestPermutation[i]].coordinates[j] << " ";
        }
        file << data[bestPermutation[i]].coordinates[dimension - 1] << std::endl;
    }

    file.close();
}

void DataSet::testBestResult(double result, std::vector<int> permutation)
{
    if (result < bestResult) {
        bestResult = result;
        std::copy(permutation.begin(), permutation.end(), bestPermutation.begin());
    }
}

const std::vector<DataSet::DataElement> &DataSet::getData() const
{
    return data;
}

int DataSet::getPermutationSize() const
{
    return permutationSize;
}

double DataSet::getBestResult() const
{
    return bestResult;
}

const std::vector<int>& DataSet::getBestPermutation() const
{
    return bestPermutation;
}
