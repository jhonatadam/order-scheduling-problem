#ifndef DEA_H
#define DEA_H

#include <queue>

#include <optimizationmethod.h>

class DEA : public OptimizationMethod
{
    // tamanho da populaçao
    unsigned popSize;
    //percentual de seleção
    unsigned eliteSize;
    // taxa de aprendizado
    double alpha;
    // número de iterações
    unsigned iteration;
    default_random_engine generator;

public:
    DEA(unsigned popSize, double eliteRatio, double alpha,
        unsigned iteration, const Instance* inst = nullptr);

    void _run() override;

    Solution *newSample(vector<double> &mean, vector<double> &stddev);
    void sample(vector<Solution*> &elite, vector<double> &mean, vector<double> &stddev);
    void update(vector<Solution*> &elite, vector<double> &mean, vector<double> &stddev);
};

#endif // DEA_H
