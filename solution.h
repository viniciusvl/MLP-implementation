#ifndef SOLUTON_H
#define SOLUTION_H

#include <vector>

struct Solution
{
    std::vector<int> route;
    double cost = 0;

    double calculateCost();
    void print();
};




#endif