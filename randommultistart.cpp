#include "randommultistart.h"

RandomMultiStart::RandomMultiStart(const Instance &inst,
                                   const unsigned numberOfIterations) :
    OptimizationMethod(inst)
{
    this->numberOfIterations = numberOfIterations;
}

void RandomMultiStart::_run()
{
    HillClimbing hc(solution);
    for (unsigned i = 0; i < numberOfIterations; i++) {
        hc.getSolution().shuffle();
        hc._run();
        if (hc.getSolution().objectiveFunc() < solution.objectiveFunc()) {
            solution.copy(hc.getSolution());
            cout << "Improve solutiion to " << solution.objectiveFunc() << endl;
        }
    }
}
