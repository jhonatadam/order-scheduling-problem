#include "localsearchs/swapls.h"

SwapLS::SwapLS()
{

}

SwapLS::~SwapLS()
{

}

bool SwapLS::firstImprovement(Solution &sol)
{
    bool improv = false;
    for (unsigned slotA = 0; slotA < sol.getNumOfSlots() - 1; slotA++) {
        for (unsigned slotB = sol.getNumOfSlots() - 1; !sol.sameTardAcc(slotA, slotB); slotB--) {
            if(sol.swapGain(slotA, slotB) < 0) {
                sol.swap(slotA, slotB);
//                cout << sol.getValue() << endl;
//                return true;
                improv = true;
            }
        }
    }
    return improv;
//    return false;
}

bool SwapLS::bestImprovement(Solution &sol)
{
    bool improved = false;
    unsigned bestValue = sol.getValue();
    pair<unsigned, unsigned> bestSwap;

    for (unsigned slotA = 0; slotA < sol.getNumOfSlots() - 1; slotA++) {
        for (unsigned slotB = sol.getNumOfSlots() - 1; !sol.sameTardAcc(slotA, slotB); slotB--) {
            unsigned newValue = unsigned(int(sol.getValue()) + sol.swapGain(slotA, slotB));
            if(newValue < bestValue) {
                bestValue = newValue;
                bestSwap = make_pair(slotA, slotB);
                improved = true;
            }
        }
    }

    if (improved) {
        sol.swap(bestSwap.first, bestSwap.second);
        cout << sol.getValue() << endl;
    }


    return improved;
}
