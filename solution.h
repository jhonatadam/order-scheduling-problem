#ifndef SOLUTION_H
#define SOLUTION_H

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

    // objective function
    double objectiveFunc();
    // evaluation functions
    double evaluationFunc();

    size_t getNumOfSlots() const;
};

#endif // SOLUTION_H
