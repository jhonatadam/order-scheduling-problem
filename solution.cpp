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

void Solution::shuffle()
{
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(scheduling.begin(), scheduling.end(), std::default_random_engine(seed));
}

void Solution::copy(const Solution &other)
{
    if (instance.numberOfOrders != other.scheduling.size()) {
        cerr << "Solution::copy: copied solution must be to the same instance" << endl;
        exit(0);
    }

    this->scheduling.assign(other.scheduling.begin(), other.scheduling.end());
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

const Instance &Solution::getInstance() const
{
    return instance;
}

