#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>

class Solution
{


    std::vector<unsigned> scheduling;

public:
    Solution(size_t numberOfOrders);

    // update functions
    // swap the orders at two given slots A and B
    void swap(size_t slotA, size_t slotB);
    // shift order of a given slot
    void shift(size_t slot);

    // objective function
    double objectiveFunc();
    // evaluation functions
    double evaluationFunc();
};

#endif // SOLUTION_H
