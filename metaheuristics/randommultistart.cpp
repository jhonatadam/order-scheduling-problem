#include "metaheuristics/randommultistart.h"

RandomMultiStart::RandomMultiStart(const Instance &inst,
                                   const unsigned numberOfIterations) :
    OptimizationMethod(inst)
{
    this->name = "Random Multistart";
    this->numberOfIterations = numberOfIterations;
}

void RandomMultiStart::_run()
{
    // display header
    string solVal = to_string(solution.getValue());
    cout << "RMS----------+" << endl;
    cout << "Best         |" << endl;
    cout << string(12 - solVal.length(), ' ') + solVal + " |" << endl;

    // running method
    HillClimbing hc(solution);
    for (unsigned i = 0; i < numberOfIterations; i++) {
        hc.getSolution().shuffle();
        hc._run();
        if (hc.getSolution().getValue() < solution.getValue()) {
            solution.copy(hc.getSolution());

            // reporting
            solVal = to_string(solution.getValue());
            cout << string(12 - solVal.length(), ' ') + solVal + " |" << endl;
        }
    }
}
