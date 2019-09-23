#include "benchmark.h"

Benchmark::Benchmark(const string &instancesFolder, const vector<OptimizationMethod *> &oms):
    oms(oms)
{
    loadInstances(instancesFolder);
}

void Benchmark::loadInstances(const string &instancesFolder)
{
    instancesFolder.at(10);
    // carregar instancias de uma dada pasta
}

void Benchmark::run()
{
    for (OptimizationMethod * om : oms) {
        for (Instance& inst : instances) {
            om->run();

            Experiment exp;
            exp.methodName      =                om->getName();
            exp.instance        =                    inst.name;
            exp.schedulingValue = om->getSolution().getValue();
            exp.execTime        =         om->getElapsedTime();
            exp.scheduling.assign(om->getSolution().getScheduling().begin(),
                                  om->getSolution().getScheduling().end());

            experiments.push_back(exp);

            cout << exp.toString() << endl;
        }
    }
}

string Experiment::toString()
{
    string str = this->methodName + ", " +
            this->instance + ", " +
            to_string(this->schedulingValue) + ", " +
            to_string(this->execTime);

    return str;
}
