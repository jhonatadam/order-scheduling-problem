#include "metaheuristics/variableneighborhooddescendant.h"

VariableNeighborhoodDescendant::VariableNeighborhoodDescendant(const Instance *inst) :
    OptimizationMethod(inst)
{
    this->name = "Variable Neighborhood Descendant";
    lss.push_back(new SwapLS());
//    lss.push_back(new ShiftLS());
}

VariableNeighborhoodDescendant::~VariableNeighborhoodDescendant()
{
    for (LocalSearch* ls: lss)
        delete ls;
}

void VariableNeighborhoodDescendant::_run()
{
    // current neighborhood
    unsigned nbh = 0;
    while (nbh < lss.size()) {
        if (lss[nbh]->firstImprovement(solution)) {
            nbh = 0;
        } else {
            nbh++;
        }
    }
}
