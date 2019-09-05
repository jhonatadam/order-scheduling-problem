#include "solution.h"

Solution::Solution(const Instance &instance) :
    instance(instance), scheduling(instance.numberOfOrders)
{
    for (unsigned slot = 0; slot < instance.numberOfOrders; slot++) {
        scheduling[slot] = slot;
    }
}

void Solution::swap(size_t slotA, size_t slotB)
{
    unsigned aux = scheduling[slotA];
    scheduling[slotA] = scheduling[slotB];
    scheduling[slotB] = aux;
}

double Solution::objectiveFunc() const
{
    // computing the lateness of each order
    vector<unsigned> ordLate(instance.numberOfOrders, 0);
    for (unsigned mac = 0; mac < instance.numberOfMachines; mac++) {
        unsigned timeSum = 0;
        for (unsigned slot = 0; slot < scheduling.size(); slot++) {
            unsigned ord = scheduling[slot];
            timeSum += instance.orderMachine[ord][mac];
            // if there is lateness
            if (timeSum > instance.dueDates[ord])
                ordLate[slot] = max(ordLate[slot], timeSum - instance.dueDates[ord]);
        }
    }

    // computing total lateness
    unsigned lateSum = 0;
    for (unsigned late : ordLate) {
        lateSum += late;
    }

    return double(lateSum);
}

size_t Solution::getNumOfSlots() const
{
    return this->scheduling.size();
}
