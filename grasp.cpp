#include "grasp.h"

GRASP::GRASP(unsigned numOfIte, unsigned numOfCand, const Instance *inst) :
    OptimizationMethod(inst), numOfIte(numOfIte)
{
    heuristic = new MinDueDateHeuristic(numOfCand);
//    heuristic = new LaterOnFirst(numOfCand);
}

GRASP::~GRASP()
{
    delete heuristic;
}

void GRASP::_run()
{
    VariableNeighborhoodDescendant vnd;
    heuristic->setInstance(solution.getInstance());

    for (size_t ite = 0; ite < numOfIte; ite++) {
        heuristic->run();

        vnd.setSolution(heuristic->getSolution());
        vnd.run();
        cout << "aqui" << endl;
        if (vnd.getSolutionValue() < this->solution.getValue()) {
            this->solution.copy(vnd.getSolution());
            cout << this->solution.getValue() << endl;
        }
    }

}
