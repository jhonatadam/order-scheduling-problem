#include "hillclimbing.h"


HillClimbing::HillClimbing(const Instance &inst, Neighborhood nbh) :
    OptimizationMethod(inst)
{
    this->setNeighborhood(nbh);
}

HillClimbing::HillClimbing(const Solution &solution, Neighborhood nbh):
    OptimizationMethod(solution)
{
    this->setNeighborhood(nbh);
}

HillClimbing::~HillClimbing()
{
    if (ls != nullptr)
        delete ls;
}

void HillClimbing::_run()
{
    while(ls->bestImprovement(solution));
}

void HillClimbing::setNeighborhood(Neighborhood nbh)
{
    if (ls != nullptr)
        delete ls;

    if (nbh == Swap)
        ls = new SwapLS();
    else if (nbh == Shift)
        ls = new ShiftLS();
}
