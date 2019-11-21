#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <optimizationmethod.h>

class GeneticAlgorithm : public OptimizationMethod
{
    // número de iterações
    unsigned iterations;
    // tamanho da população
    unsigned popSize;
     // número de indivíduos por torneio
    unsigned k;
     // percentual da população que se tornará pai
    double crossRate;
     // percentual dos pais que soferá mutação
    double mutateRate;
    vector<Solution*> pool;
    default_random_engine generator;

    void initPopulation(vector<Solution*> &pop);
    void selectParents(vector<Solution*> &source, vector<Solution*> &selected);
    Solution* mutate(Solution *s);
    bool exists(vector<Solution *> &vector, Solution* s);
    Solution* OX(Solution *s1, Solution *s2);
    Solution* randomX(Solution* s1, Solution* s2, double x);

public:
    GeneticAlgorithm(unsigned iterations, unsigned popSize, unsigned k,
                     double mutateRate, double crossRate, const Instance *inst = nullptr);


    void _run() override;
};

#endif // GENETICALGORITHM_H
