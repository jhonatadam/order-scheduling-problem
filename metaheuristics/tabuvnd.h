#ifndef TABUVND_H
#define TABUVND_H

#include <list>

#include <metaheuristics/variableneighborhooddescendant.h>


class TabuVND : public VariableNeighborhoodDescendant
{
    Tabu *tabu;
public:
    TabuVND(Tabu *tabu, const Instance *inst);

    void _run() override;
};

#endif // TABUVND_H
