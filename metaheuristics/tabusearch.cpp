#include "tabusearch.h"

TabuSearch::TabuSearch(unsigned tenure, unsigned iterations, const Instance *inst) :
    OptimizationMethod(inst), tabu(tenure), iterations(iterations)
{

}

void TabuSearch::_run()
{
    TabuVND vnd(&tabu, solution.getInstance());

    for (unsigned i = 0; i < iterations; i++) {
        vnd.run();

        if (vnd.getSolutionValue() < solution.getValue()) {
            solution.copy(vnd.getSolution());
            tabu.clean();

            cout << i << " " << solution.getValue() << endl;
        }
        tabu.insert(vnd.getSolution());
        do {
            vnd.getSolution().shuffle();
        } while (tabu.contains(vnd.getSolution()));
    }
}
