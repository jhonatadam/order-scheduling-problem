#include "shiftls.h"

ShiftLS::ShiftLS()
{

}

bool ShiftLS::firstImprovement(Solution &sol)
{
    unsigned bestValue = sol.getValue();
    unsigned firstLate = sol.getFirstLate();

    for (unsigned slotA = 0; slotA < sol.getNumOfSlots(); slotA++) {
        sol.shift(slotA, firstLate);

        for (unsigned slotB = firstLate; slotB < sol.getNumOfSlots(); slotB++) {
            unsigned newValue = sol.getValue();

            if(newValue < bestValue)
                return true;

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
        sol.shift(slotA, firstLate);

        for (unsigned slotB = firstLate; slotB < sol.getNumOfSlots(); slotB++) {
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
