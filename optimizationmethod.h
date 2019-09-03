#ifndef OPTIMIZATIONMETHOD_H
#define OPTIMIZATIONMETHOD_H


class OptimizationMethod
{
public:
    OptimizationMethod();
    virtual ~OptimizationMethod() = 0;

    virtual bool run() = 0;

};

#endif // OPTIMIZATIONMETHOD_H
