#include "metaheuristics/iteratedlocalsearch.h"


IteratedLocalSearch::IteratedLocalSearch(unsigned numberOfIterations,
                                         unsigned swapsPerPerturb,
                                         const Instance *inst) :
    OptimizationMethod(inst), numberOfIterations(numberOfIterations),
    swapsPerPerturb(swapsPerPerturb)
{
    this->name = "Iterated Local Search";
}

void IteratedLocalSearch::_run()
{
    // display header
    string solVal = to_string(solution.getValue());
    cout << "ILS----------+" << endl;
    cout << "Best         |" << endl;
    cout << string(12 - solVal.length(), ' ') + solVal + " |" << endl;

    // running method
    HillClimbing hc(solution);
    hc.getSolution().shuffle();
    for (unsigned i = 0; i < numberOfIterations; i++) {
        hc.getSolution().perturbBySwap(swapsPerPerturb);
        hc._run();
        if (hc.getSolutionValue() < solution.getValue()) {
            solution.copy(hc.getSolution());

            // reporting
            solVal = to_string(solution.getValue());
            cout << string(12 - solVal.length(), ' ') + solVal + " |" << endl;
        }
    }
}
