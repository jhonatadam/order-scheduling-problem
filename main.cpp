#include <metaheuristics/iteratedlocalsearch.h>
#include <metaheuristics/randommultistart.h>
#include <metaheuristics/variableneighborhoodsearch.h>
#include <grasp.h>

#include <benchmark.h>

int main()
{

    // loading instance
    string instFolder = "../order-scheduling-problem/instances/big/";
    string instName   = "bt_0.8_0.8_0160";
    Instance instance(instFolder, instName);

    vector<tuple<Neighborhood, size_t, size_t>> neighborhoods;
    neighborhoods.push_back(make_tuple(Swap, 10, 10));
    neighborhoods.push_back(make_tuple(Shift, 10, 10));
    neighborhoods.push_back(make_tuple(Swap, 25, 5));
    neighborhoods.push_back(make_tuple(Shift, 25, 5));

    vector<OptimizationMethod *> optMethods;
    optMethods.push_back(new GRASP(30, 5));
    optMethods.push_back(new VariableNeighborhoodDescendant);
//    optMethods.push_back(new MinDueDateHeuristic(4));
//    optMethods.push_back(new LaterOnFirst(3));
//    optMethods.push_back(new HillClimbing);
//    optMethods.push_back(new IteratedLocalSearch(1, 20));
//    optMethods.push_back(new RandomMultiStart(5));

    OptimizationMethod *om = new VariableNeighborhoodDescendant(&instance);
    om->run();

    cout << "Value: " << om->getSolutionValue() << endl;
    cout << "Time : " << om->getElapsedTime() << endl;


    // initilizing benchmark
//    Benchmark bm(instFolder, optMethods);

    // running benchmark
//    bm.run();

    // showing resoults
//    cout << "Solution value: " << om->getSolutionValue() << endl;
//    cout << "Elapsed time:   " << om->getElapsedTime() << " seconds" << endl;

    // cleaning memory
    for (OptimizationMethod * om : optMethods)
        delete om;

    return 0;
}
