#include "solution.h"

Solution::Solution(size_t numberOfOrders) :
    scheduling(numberOfOrders)
{
    for (unsigned slot = 0; slot < numberOfOrders; slot++) {
        scheduling[slot] = slot;
    }
}
