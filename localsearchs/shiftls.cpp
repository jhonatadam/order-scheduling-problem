#include "localsearchs/shiftls.h"

ShiftLS::ShiftLS()
{

}

ShiftLS::~ShiftLS()
{

}

bool ShiftLS::firstImprovement(Solution &sol)
{
    unsigned bestValue = sol.getValue();
    unsigned firstLate = sol.getFirstLate();

    for (unsigned slotA = 0; slotA < sol.getNumOfSlots(); slotA++) {
        unsigned begin = (slotA < firstLate ? firstLate : 0);
        sol.shift(slotA, begin);

        for (unsigned slotB = begin; slotB < sol.getNumOfSlots(); slotB++) {
            unsigned newValue = sol.getValue();
            if(newValue < bestValue) {
                return true;
            }

            if ((slotB + 1) < sol.getNumOfSlots())
                sol.swap(slotB, slotB + 1);
        }

        sol.shift(sol.getNumOfSlots() - 1, slotA);
    }

    return false;
}

bool ShiftLS::firstImprovement(Solution &sol, vector<vector<unsigned int> > &penalities)
{
    unsigned firstLate = sol.getFirstLate();
    // solution evaluation
    unsigned bestEvaluation = sol.getValue();
    for (unsigned slot = 0; slot < sol.getNumOfSlots(); slot++)
        bestEvaluation += penalities[sol.getOrder(slot)][slot];

    for (unsigned slotA = 0; slotA < sol.getNumOfSlots(); slotA++) {
        unsigned begin = (slotA < firstLate ? firstLate : 0);
        sol.shift(slotA, begin);

        for (unsigned slotB = begin; slotB < sol.getNumOfSlots(); slotB++) {
            // new solution evaluation
            unsigned newEvaluation = sol.getValue();
            for (unsigned slot = 0; slot < sol.getNumOfSlots(); slot++)
                newEvaluation += penalities[sol.getOrder(slot)][slot];

            if(newEvaluation < bestEvaluation) {
                return true;
            }

            if ((slotB + 1) < sol.getNumOfSlots())
                sol.swap(slotB, slotB + 1);
        }

        sol.shift(sol.getNumOfSlots() - 1, slotA);
    }

    return false;
}

bool ShiftLS::firstImprovement(Solution &sol, Tabu *tabu)
{
    unsigned initValue = sol.getValue();
    unsigned firstLate = sol.getFirstLate();

    for (unsigned slotA = 0; slotA < sol.getNumOfSlots(); slotA++) {
        unsigned begin = (slotA < firstLate ? firstLate : 0);
        sol.shift(slotA, begin);

        for (unsigned slotB = begin; slotB < sol.getNumOfSlots(); slotB++) {
            if((sol.getValue() < initValue) && !tabu->contains(sol)) {
                return true;
            }

            if ((slotB + 1) < sol.getNumOfSlots())
                sol.swap(slotB, slotB + 1);
        }

        sol.shift(sol.getNumOfSlots() - 1, slotA);
    }

    return false;
}

bool ShiftLS::bestImprovement(Solution &sol)
{
    bool improved = false;
    unsigned bestValue = sol.getValue();
    pair<unsigned, unsigned> bestShift;
    unsigned firstLate = sol.getFirstLate();

    for (unsigned slotA = 0; slotA < sol.getNumOfSlots(); slotA++) {
        unsigned begin = (slotA < firstLate ? firstLate : 0);
        sol.shift(slotA, begin);

        for (unsigned slotB = begin; slotB < sol.getNumOfSlots(); slotB++) {
            unsigned newValue = sol.getValue();

            if(newValue < bestValue) {
                bestValue = newValue;
                bestShift = make_pair(slotA, slotB);
                improved = true;
            }

            if ((slotB + 1) < sol.getNumOfSlots())
                sol.swap(slotB, slotB + 1);
        }
        sol.shift(sol.getNumOfSlots() - 1, slotA);
    }

    if (improved)
        sol.shift(bestShift.first, bestShift.second);

    return improved;
}

bool ShiftLS::bestImprovement(Solution &sol, vector<vector<unsigned int> > &penalities)
{
    return false;
}

bool ShiftLS::bestImprovement(Solution &sol, Tabu *tabu)
{
    return false;
}
