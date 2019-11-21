#ifndef SCATTERSEARCH_H
#define SCATTERSEARCH_H

#include <metaheuristics/hillclimbing.h>
#include <heuristics/lateronfirst.h>
#include <heuristics/minduedateheuristic.h>

class ScatterSearch : public OptimizationMethod
{
    unsigned iterations;
    unsigned popIniSize;
    unsigned eliteSize;
    double step = 0.005;

    // random generator
    default_random_engine generator;

    unsigned getDistance(Solution* s1, Solution* s2);
    void initPopulation(vector<Solution*> &population);
    void selectElite(vector<Solution*> &population, vector<Solution*> &elite);
    void OX(Solution*& son, Solution *s1, Solution *s2);
    void randomX(Solution *&son, Solution *s1, Solution *s2, double x);
    void pathRelinking(Solution *&son, Solution *s1, Solution *s2);

public:
    ScatterSearch(unsigned iterations, unsigned popIniSize,
                  unsigned eliteSize, const Instance *inst);

    void _run() override;
};

#endif // SCATTERSEARCH_H
