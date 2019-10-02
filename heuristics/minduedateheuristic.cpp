#include "heuristics/minduedateheuristic.h"


MinDueDateHeuristic::MinDueDateHeuristic(const unsigned numOfCand, const Instance *inst) :
    OptimizationMethod(inst), numOfCand(numOfCand)
{
    this->name = "Min Due Date";
}

void MinDueDateHeuristic::_run()
{
    tempSched.resize(solution.getNumOfSlots());

    for (unsigned slot = 0; slot < solution.getNumOfSlots(); slot++)
        tempSched[slot] = solution.getOrder(slot);


    auto lessThan = [this](size_t orderA, size_t orderB) -> bool {
         return (this->solution.getInstance()->dueDates[orderA] <
                 this->solution.getInstance()->dueDates[orderB]);
    };

    sort(tempSched.begin(), tempSched.end(), lessThan);

    // random generator
    long seed = 0; // chrono::system_clock::now().time_since_epoch().count();
    default_random_engine randGenerator(seed);


    for (size_t slot = 0; slot < solution.getNumOfSlots(); slot++) {
        // uniform distribution between 0 and swapsPerPerturb
        uniform_int_distribution<size_t> randDistribution(slot,
            min(slot + numOfCand - 1, solution.getNumOfSlots() - 1));

        size_t next = randDistribution(randGenerator);
        if (next != slot)
            swap(tempSched[slot], tempSched[next]);
    }

    solution.setScheduling(tempSched);
}
