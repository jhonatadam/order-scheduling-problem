#include "hillclimbing.h"

HillClimbing::HillClimbing(const Instance &inst) :
    sol(inst)
{
    ls = new SwapLS();
}

HillClimbing::~HillClimbing()
{
    if (ls != nullptr)
        delete ls;
}

bool HillClimbing::run()
{
    while(ls->firstImprovement(sol));
    cout << sol.objectiveFunc() << endl;
    return true;
}
