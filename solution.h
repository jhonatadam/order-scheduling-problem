#ifndef SOLUTION_H
#define SOLUTION_H

#include <chrono>
#include <algorithm>
#include <random>

#include <instance.h>

class Solution
{
    const Instance &instance;

    std::vector<unsigned> scheduling;

public:
    Solution(const Instance &instance);

    // update functions
    // swap the orders at two given slots A and B
    void swap(size_t slotA, size_t slotB);
    // shift order of a given slot
    void shift(size_t slot);
    // shuffle current scheduling
    void shuffle();
    // copy scheduling of other solution to the same instance
    void copy(const Solution &other);

    // objective function
    double objectiveFunc() const;
    // evaluation functions
    double evaluationFunc() const;

    size_t getNumOfSlots() const;
    const Instance &getInstance() const;
};

#endif // SOLUTION_H
