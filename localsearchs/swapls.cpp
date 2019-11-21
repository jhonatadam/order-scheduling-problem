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
        for (unsigned slotB = unsigned(sol.getNumOfSlots() - 1); !sol.sameTardAcc(slotA, slotB); slotB--) {
            if(sol.swapGain(slotA, slotB) < 0) {
                sol.swap(slotA, slotB);
                improv = true;
            }
        }
    }
    return improv;
}

bool SwapLS::firstImprovement(Solution &sol, vector<vector<unsigned int> > &penalities)
{
    bool improve = false;
    for (unsigned slotA = 0; slotA < sol.getNumOfSlots() - 1; slotA++) {
        for (unsigned slotB = unsigned(sol.getNumOfSlots() - 1); !sol.sameTardAcc(slotA, slotB); slotB--) {
            int swapGain = sol.swapGain(slotA, slotB);
            // order penalty of slot a be in slot b and vice-versa
            swapGain += int(penalities[sol.getOrder(slotA)][slotB] + penalities[sol.getOrder(slotB)][slotA]);
            // removing penalities before the swap
            swapGain -= int(penalities[sol.getOrder(slotA)][slotA] + penalities[sol.getOrder(slotB)][slotB]);

            if(swapGain < 0) {
                sol.swap(slotA, slotB);
                improve = true;
            }
        }
    }
    return improve;


}

bool SwapLS::firstImprovement(Solution &sol, Tabu *tabu)
{
    bool improv = false;
    for (unsigned slotA = 0; slotA < sol.getNumOfSlots() - 1; slotA++) {
        for (unsigned slotB = unsigned(sol.getNumOfSlots() - 1); !sol.sameTardAcc(slotA, slotB); slotB--) {
            if(sol.swapGain(slotA, slotB) < 0) {
                sol.swap(slotA, slotB);
                if (!tabu->contains(sol))
                    improv = true;
            }
        }
    }
    return improv;
}

bool SwapLS::bestImprovement(Solution &sol)
{
    bool improved = false;
    unsigned bestValue = sol.getValue();
    pair<unsigned, unsigned> bestSwap;

    for (unsigned slotA = 0; slotA < sol.getNumOfSlots() - 1; slotA++) {
        for (unsigned slotB = unsigned(sol.getNumOfSlots() - 1); !sol.sameTardAcc(slotA, slotB); slotB--) {
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

bool SwapLS::bestImprovement(Solution &sol, vector<vector<unsigned int> > &penalities)
{
    return false;
}

bool SwapLS::bestImprovement(Solution &sol, Tabu *tabu)
{
    return false;
}
