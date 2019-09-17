#include "lateronfirst.h"

LaterOnFirst::LaterOnFirst(const Instance &inst) :
    OptimizationMethod(inst)
{

}

void LaterOnFirst::_run()
{
    vector<unsigned> scheduling(solution.getNumOfSlots());
    for (unsigned slot = 0; slot < solution.getNumOfSlots(); slot++)
        scheduling[slot] = solution.getOrder(slot);

    vector<unsigned> timeAcc(solution.getInstance().numberOfMachines, 0);

    for (unsigned begin = 0; begin < solution.getNumOfSlots() - 1; begin++) {

        unsigned later = numeric_limits<unsigned>::max();
        int lateness = numeric_limits<int>::min();

        for (unsigned slot = begin; slot < solution.getNumOfSlots(); slot++) {

            unsigned maxTime = 0;
            unsigned order = scheduling[slot];

            for (unsigned mach = 0; mach < solution.getInstance().numberOfMachines; mach++) {
                if ((solution.getInstance().orderMachine[order][mach] + timeAcc[mach]) > maxTime)
                    maxTime = solution.getInstance().orderMachine[order][mach] + timeAcc[mach];
            }

            int newLateness = int(maxTime) - int(solution.getInstance().dueDates[order]);
            if (newLateness > lateness) {
                later = slot;
                lateness = newLateness;
            }

        }

        unsigned aux = scheduling[begin];
        scheduling[begin] = scheduling[later];
        scheduling[later] = aux;

        for (unsigned mach = 0; mach < solution.getInstance().numberOfMachines; mach++) {
            timeAcc[mach] += solution.getInstance().orderMachine[scheduling[begin]][mach];
        }
    }

    solution.setScheduling(scheduling);
}
