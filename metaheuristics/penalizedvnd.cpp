#include "penalizedvnd.h"

PenalizedVND::PenalizedVND(const Instance *inst, vector<vector<unsigned> > *penalities) :
    VariableNeighborhoodDescendant(inst), penalities(penalities)
{

}

void PenalizedVND::_run()
{
    // current neighborhood
    unsigned nbh = 0;
    while (nbh < lss.size()) {
        if (lss[nbh]->firstImprovement(solution, *penalities)) {
            nbh = 0;
        } else {
            nbh++;
        }
    }
}
