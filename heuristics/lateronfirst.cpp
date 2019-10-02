#include "heuristics/lateronfirst.h"


LaterOnFirst::LaterOnFirst(unsigned numOfCand, const Instance *inst) :
    OptimizationMethod(inst), numOfCand(numOfCand)
{
    this->name = "Later on First";
}

void LaterOnFirst::_run()
{
    vector<unsigned> scheduling(solution.getNumOfSlots());
    for (unsigned slot = 0; slot < solution.getNumOfSlots(); slot++)
        scheduling[slot] = solution.getOrder(slot);

    vector<unsigned> timeAcc(solution.getInstance()->numberOfMachines, 0);

    for (unsigned begin = 0; begin < solution.getNumOfSlots() - 1; begin++) {

        unsigned later = numeric_limits<unsigned>::max();
        int lateness = numeric_limits<int>::min();

        for (unsigned slot = begin; slot < solution.getNumOfSlots(); slot++) {

            unsigned maxTime = 0;
            unsigned order = scheduling[slot];

            for (unsigned mach = 0; mach < solution.getInstance()->numberOfMachines; mach++) {
                if ((solution.getInstance()->orderMachine[order][mach] + timeAcc[mach]) > maxTime)
                    maxTime = solution.getInstance()->orderMachine[order][mach] + timeAcc[mach];
            }

            int newLateness = int(maxTime) - int(solution.getInstance()->dueDates[order]);
            if (newLateness > lateness) {
                later = slot;
                lateness = newLateness;
            }

        }

        unsigned aux = scheduling[begin];
        scheduling[begin] = scheduling[later];
        scheduling[later] = aux;

        for (unsigned mach = 0; mach < solution.getInstance()->numberOfMachines; mach++) {
            timeAcc[mach] += solution.getInstance()->orderMachine[scheduling[begin]][mach];
        }
    }

    // random generator
    long seed = 0; // chrono::system_clock::now().time_since_epoch().count();
    default_random_engine randGenerator(seed);

    for (size_t slot = 0; slot < solution.getNumOfSlots(); slot++) {
        // uniform distribution between 0 and swapsPerPerturb
        uniform_int_distribution<size_t> randDistribution(slot,
            min(slot + numOfCand - 1, solution.getNumOfSlots() - 1));

        size_t next = randDistribution(randGenerator);
        if (next != slot)
            swap(scheduling[slot], scheduling[next]);
    }

    solution.setScheduling(scheduling);
}
