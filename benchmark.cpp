#include "benchmark.h"

Benchmark::Benchmark(const string &instDir, const vector<OptimizationMethod *> &optMethods):
    optMethods(optMethods)
{
    loadInstances(instDir);
}

Benchmark::~Benchmark()
{
    this->clean();
}

void Benchmark::loadInstances(const string &instDir)
{
    DIR* dirp = opendir(instDir.c_str());
    struct dirent * dp;

    if (!dirp)
        cerr << "O diretorio de instancias nao existe." << endl;

    while ((dp = readdir(dirp)) != nullptr) {
        if (dp->d_type != DT_DIR) {
            instances.push_back(new Instance(instDir, dp->d_name));
        }
    }

    closedir(dirp);
}

void Benchmark::run()
{
    // experiment index
    size_t exp = 0;
    // setting experiments vector
    experiments.resize(instances.size() * optMethods.size());

    // running experiments
    for (Instance* inst : instances) {
        for (OptimizationMethod * om : optMethods) {
            // setting instance
            om->setInstance(inst);

            // running method
            om->run();

            // saving results
            experiments[exp] = new Experiment(inst, om);

            // diplaing results
            cout << experiments[exp]->toString() << endl;

            exp++;
        }
        cout << float(exp)/experiments.size() * 100 << "%" << endl;
    }
}

void Benchmark::clean()
{
    for (Instance *inst : instances)
        delete inst;

    for (Experiment *exp : experiments)
        delete exp;
}

Experiment::Experiment(Instance *inst, OptimizationMethod *optMethod)
{
    this->instName   =                         inst->name;
    this->methodName =               optMethod->getName();
    this->runtime    =        optMethod->getElapsedTime();
    this->schedValue =      optMethod->getSolutionValue();
    this->scheduling = new unsigned[inst->numberOfOrders];

    for (unsigned i = 0; i < inst->numberOfOrders; i++)
        this->scheduling[i] = optMethod->getSolution().getOrder(i);
}

Experiment::~Experiment()
{
    delete[] scheduling;
}

string Experiment::toString()
{
    string str = this->instName + ", " +
            this->methodName + ", " +
            to_string(this->runtime) + ", " +
            to_string(this->schedValue);

    return str;
}
