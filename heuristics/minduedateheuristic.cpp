#include "heuristics/minduedateheuristic.h"


MinDueDateHeuristic::MinDueDateHeuristic(const Instance &inst) :
    OptimizationMethod(inst)
{
    this->name = "Min Due Date";
}

void MinDueDateHeuristic::_run()
{
    vector<unsigned> scheduling(solution.getNumOfSlots());
    for (unsigned slot = 0; slot < solution.getNumOfSlots(); slot++)
        scheduling[slot] = solution.getOrder(slot);

    auto lessThan = [this](size_t orderA, size_t orderB) -> bool {
         return (this->solution.getInstance().dueDates[orderA] <
                 this->solution.getInstance().dueDates[orderB]);
    };

    sort(scheduling.begin(), scheduling.end(), lessThan);

    solution.setScheduling(scheduling);
}
