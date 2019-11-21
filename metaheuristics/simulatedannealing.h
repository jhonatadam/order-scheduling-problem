#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H


#include <metaheuristics/hillclimbing.h>


class SimulatedAnnealing : public OptimizationMethod
{

     // probabilidade de se ter um pioramento de B na temperatura inicial
    double initialProb = 0.5;
    // probabilidade de se ter um pioramento de B na temperatura final
    double endProb = 0.001;
    // pioramento permitido com probabilidade A
    double worsening = 0.001;
    // número de iterações
    unsigned iterations = 25;

public:
    SimulatedAnnealing(double initialProb, double endProb, double worsening, unsigned iterations, const Instance *inst);

    void _run() override;
};

#endif // SIMULATEDANNEALING_H
