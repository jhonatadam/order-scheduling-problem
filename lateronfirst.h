#ifndef LATERONFIRST_H
#define LATERONFIRST_H

#include <limits>

#include <optimizationmethod.h>

class LaterOnFirst : public OptimizationMethod
{
public:
    LaterOnFirst(const Instance &inst);

    void _run() override;
};

#endif // LATERONFIRST_H
