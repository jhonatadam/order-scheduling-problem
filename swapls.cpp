#include "swapls.h"

SwapLS::SwapLS()
{

}

SwapLS::~SwapLS()
{

}

bool SwapLS::firstImprovement(Solution &sol)
{
    double bestValue = sol.objectiveFunc();
    for (unsigned slotA = 0; slotA < sol.getNumOfSlots(); slotA++) {
        for (unsigned slotB = slotA+1; slotB < sol.getNumOfSlots(); slotB++) {
            sol.swap(slotA, slotB);
            double newValue = sol.objectiveFunc();
            if(newValue < bestValue)
                return true;
            sol.swap(slotA, slotB);
        }
    }
    return false;
}

bool SwapLS::bestImprovement(Solution &sol)
{
    bool improved = false;
    double bestValue = sol.objectiveFunc();
    pair<unsigned, unsigned> bestSwap;

    for (unsigned slotA = 0; slotA < sol.getNumOfSlots(); slotA++) {
        for (unsigned slotB = slotA+1; slotB < sol.getNumOfSlots(); slotB++) {
            sol.swap(slotA, slotB);
            double newValue = sol.objectiveFunc();
            if(newValue < bestValue) {
                bestValue = newValue;
                bestSwap = make_pair(slotA, slotB);
                improved = true;
            }
            sol.swap(slotA, slotB);
        }
    }

    if (improved)
        sol.swap(bestSwap.first, bestSwap.second);

    return improved;
}
