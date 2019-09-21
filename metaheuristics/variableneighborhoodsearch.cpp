#include "metaheuristics/variableneighborhoodsearch.h"

VariableNeighborhoodSearch::VariableNeighborhoodSearch(
        const Instance &inst, const unsigned maxIt,
        vector<tuple<Neighborhood, size_t, size_t>> &nbhs) :
    OptimizationMethod(inst), maxIt(maxIt)
{
    this->name = "Variable Neighborhood Search";
    this->nbhs.assign(nbhs.begin(), nbhs.end());
}

VariableNeighborhoodSearch::~VariableNeighborhoodSearch()
{

}

void VariableNeighborhoodSearch::_run()
{
    unsigned nbh =               0;
    unsigned it  =               0;
    size_t tries = get<2>(nbhs[0]);
    VariableNeighborhoodDescendant vnd(solution.getInstance());

    while (it < maxIt) {

        if (tries == 0) {
            nbh++;
            if (nbh == nbhs.size())
                break;

            tries = get<2>(nbhs[nbh]);
        }

        if (get<0>(nbhs[nbh]) == Swap)
            vnd.getSolution().perturbBySwap(get<1>(nbhs[nbh]));
        else if (get<0>(nbhs[nbh]) == Shift)
            vnd.getSolution().perturbByShift(get<1>(nbhs[nbh]));

        vnd._run();

        if (vnd.getSolutionValue() < solution.getValue()) {
            solution.copy(vnd.getSolution());
            tries = get<2>(nbhs[0]);
            nbh = 0;
            cout << vnd.getSolutionValue() << endl;
        } else {
            tries--;
            vnd.setSolution(solution);
        }

        it++;
    }
}
