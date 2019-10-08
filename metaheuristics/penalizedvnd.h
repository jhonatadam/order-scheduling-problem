#ifndef PENALIZEDVND_H
#define PENALIZEDVND_H

#include <metaheuristics/variableneighborhooddescendant.h>

class PenalizedVND : public VariableNeighborhoodDescendant
{
    vector<vector<unsigned>> *penalities;
public:
    PenalizedVND(const Instance *inst, vector<vector<unsigned>> *penalities);

    void _run() override;


};

#endif // PENALIZEDVND_H
