#include "iteratedlocalsearch.h"


IteratedLocalSearch::IteratedLocalSearch(const Instance &inst,
                                         unsigned numberOfIterations,
                                         unsigned swapsPerPerturb) :
    OptimizationMethod(inst), numberOfIterations(numberOfIterations),
    swapsPerPerturb(swapsPerPerturb)
{

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
