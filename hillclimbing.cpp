#include "hillclimbing.h"


HillClimbing::HillClimbing(const Instance &inst) :
    OptimizationMethod(inst)
{
    ls = new SwapLS();
}

HillClimbing::HillClimbing(const Solution &solution):
    OptimizationMethod(solution)
{
    ls = new SwapLS();
}

HillClimbing::~HillClimbing()
{
    if (ls != nullptr)
        delete ls;
}

void HillClimbing::_run()
{
    while(ls->firstImprovement(solution));
}
