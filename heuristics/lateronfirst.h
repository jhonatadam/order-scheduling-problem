#ifndef LATERONFIRST_H
#define LATERONFIRST_H

#include <limits>

#include <optimizationmethod.h>

class LaterOnFirst : public OptimizationMethod
{
    unsigned numOfCand;
public:
    LaterOnFirst(unsigned numOfCand = 1, const Instance *inst = nullptr);

    void _run() override;
};

#endif // LATERONFIRST_H
