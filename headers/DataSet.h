//
// Created by MandicFilip on 13.1.19..
//


#ifndef TSPOPTIMIZATION_DATASET_H
#define TSPOPTIMIZATION_DATASET_H


#include <string>
#include <vector>

class DataSet {

public:
    struct DataElement
    {
        std::vector<double> coordinates;
    };

    int createDataSet(std::string fileName, int dimension);
    void printBestResult(std::string fileName);
    void printJustHoles(std::string fileName);

    const std::vector<DataElement>& getData() const;

    void testBestResult(double result, std::vector<int> permutation);

    int getPermutationSize() const;

    double getBestResult() const;

    const std::vector<int>& getBestPermutation() const;

private:
    std::vector<DataElement> data;

    double bestResult;
    std::vector<int> bestPermutation;

    int permutationSize;

    int dimension;
};


#endif //TSPOPTIMIZATION_DATASET_H