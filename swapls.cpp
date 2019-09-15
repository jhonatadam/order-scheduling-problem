#include "swapls.h"

SwapLS::SwapLS()
{

}

SwapLS::~SwapLS()
{

}

bool SwapLS::firstImprovement(Solution &sol)
{
    for (unsigned slotA = 0; slotA < sol.getNumOfSlots(); slotA++) {
        for (unsigned slotB = slotA+1; slotB < sol.getNumOfSlots(); slotB++) {
            if(sol.swapGain(slotA, slotB) < 0) {
                sol.swap(slotA, slotB);
                return true;
            }
        }
    }

    return false;
}

bool SwapLS::bestImprovement(Solution &sol)
{
    bool improved = false;
    unsigned bestValue = sol.getValue();
    pair<unsigned, unsigned> bestSwap;

    for (unsigned slotA = 0; slotA < sol.getNumOfSlots(); slotA++) {
        for (unsigned slotB = slotA+1; slotB < sol.getNumOfSlots(); slotB++) {
            unsigned newValue = unsigned(int(sol.getValue()) + sol.swapGain(slotA, slotB));
            if(newValue < bestValue) {
                bestValue = newValue;
                bestSwap = make_pair(slotA, slotB);
                improved = true;
            }
        }
    }

    if (improved)
        sol.swap(bestSwap.first, bestSwap.second);

    return improved;
}
