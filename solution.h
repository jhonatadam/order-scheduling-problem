#ifndef SOLUTION_H
#define SOLUTION_H

#include <chrono>
#include <algorithm>
#include <random>

#include <instance.h>

class Solution
{
    // order scheduling problem instance
    const Instance *instance;
    // solution
    vector<unsigned> scheduling;
    // time accumulation by a each order in each
    // machine
    vector<vector<unsigned>> timeAcc;
    // tardiness accumulated in each slot
    // the solution value is manteined in last
    // position of tardinessAcc vector
    vector<unsigned> tardinessAcc;
    // swap orders in two given slots
    void _swap(size_t slotA, size_t slotB);
    // shift an order from a given slot to another one
    void _shift(size_t from, size_t to);
    // update solution value
    void updateValue(size_t begin, size_t end);
    // value gain
    int valueGain(size_t begin, size_t end);

public:
    Solution(const Instance *instance);

    // modifiers
    // swap the orders at two given slots A and B
    void swap(size_t slotA, size_t slotB);
    // calculate swap gain
    int swapGain(size_t slotA, size_t slotB);
    // shift order of a given slot
    void shift(size_t from, size_t to);
    // calculate shift gain
    int shiftGain(size_t from, size_t to);
    // shuffle current scheduling
    void shuffle();
    // copy scheduling of other solution to the same instance
    void copy(const Solution &other);
    // copy a given scheduling
    void setScheduling(const vector<unsigned> &scheduling);
    // perturb solution by swapping random orders
    void perturbBySwap(size_t numberOfSwaps);
    // perturb solution by shifting random orders
    void perturbByShift(size_t numberOfShifts);

    // getters
    unsigned getValue();
    double getEvaluation() const;
    size_t getNumOfSlots() const;
    const Instance *getInstance() const;
    unsigned getOrder(size_t slot);
    unsigned getSlot(size_t order);
    unsigned getFirstLate();

    // setters
    void setInstance(const Instance *instance);
    const vector<unsigned>& getScheduling();
};

#endif // SOLUTION_H
