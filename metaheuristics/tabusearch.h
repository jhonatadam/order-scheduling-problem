#ifndef TABUSEARCH_H
#define TABUSEARCH_H

#include <metaheuristics/tabuvnd.h>

class TabuSearch : public OptimizationMethod
{
    Tabu tabu;
    unsigned iterations;
public:
    TabuSearch(unsigned tenure, unsigned iterations, const Instance *inst = nullptr);

    void _run() override;
};

#endif // TABUSEARCH_H
