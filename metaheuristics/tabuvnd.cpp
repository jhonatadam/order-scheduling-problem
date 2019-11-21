#include "tabuvnd.h"

TabuVND::TabuVND(Tabu *tabu, const Instance *inst) :
    VariableNeighborhoodDescendant(inst), tabu(tabu)
{
}

void TabuVND::_run()
{
    // current neighborhood
    unsigned nbh = 0;
    while (nbh < lss.size()) {
        if (lss[nbh]->firstImprovement(solution, tabu)) {
            nbh = 0;
        } else {
            nbh++;
        }
    }
}
