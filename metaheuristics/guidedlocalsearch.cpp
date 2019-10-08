#include "guidedlocalsearch.h"

void GuidedLocalSearch::initilizePenalities()
{
    if (penalities.size() != solution.getNumOfSlots()) {
        penalities.resize(solution.getNumOfSlots());
        for (vector<unsigned> &v : penalities)
            v.resize(solution.getNumOfSlots(), 0);
    } else {
        for (vector<unsigned> &v : penalities)
            for (unsigned &e : v)
                e = 0;
    }
}

void GuidedLocalSearch::penalize(Solution &sol)
{
    for (unsigned slot = 0; slot < sol.getNumOfSlots(); slot++)
        penalities[sol.getOrder(slot)][slot]++;
}

GuidedLocalSearch::GuidedLocalSearch(const size_t numIt, const Instance * inst) :
    OptimizationMethod(inst), numIt(numIt)
{
    this->name = "Guided Local Search";
}

void GuidedLocalSearch::_run()
{
    initilizePenalities();
    PenalizedVND vnd(solution.getInstance(), &penalities);

    for (size_t it = 0; it < numIt; it++){
        vnd.run();
        penalize(vnd.getSolution());

        if (vnd.getSolution().getValue() < solution.getValue()){
            solution.copy(vnd.getSolution());
            cout << solution.getValue() << " " << it << endl;
        }
    }
}
