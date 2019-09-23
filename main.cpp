#include <metaheuristics/iteratedlocalsearch.h>
#include <metaheuristics/randommultistart.h>
#include <metaheuristics/variableneighborhoodsearch.h>
#include <heuristics/minduedateheuristic.h>
#include <heuristics/lateronfirst.h>

#include <benchmark.h>

int main()
{
    // loading instance
    string instFolder = "../order-scheduling-problem/instances/big/";
    string instName   = "bt_0.8_0.8_0004";
    Instance instance(instFolder, instName);

    vector<tuple<Neighborhood, size_t, size_t>> nbhs;
    nbhs.push_back(make_tuple(Swap, 10, 10));
    nbhs.push_back(make_tuple(Shift, 10, 10));
    nbhs.push_back(make_tuple(Swap, 25, 5));
    nbhs.push_back(make_tuple(Shift, 25, 5));

    vector<OptimizationMethod *> oms;
    oms.push_back(new MinDueDateHeuristic);
    oms.push_back(new LaterOnFirst);


    Benchmark bm("inst folder", oms);

    // initializing optimization method
    OptimizationMethod *om = new MinDueDateHeuristic(&instance);

    // running optimization method
    om->run();

    // showing resoults
    cout << "Solution value: " << om->getSolutionValue() << endl;
    cout << "Elapsed time:   " << om->getElapsedTime() << " seconds" << endl;

    // cleaning memory
    delete om;

    for (OptimizationMethod * om : oms)
        delete om;

    return 0;
}
