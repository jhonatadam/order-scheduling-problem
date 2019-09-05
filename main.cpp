#include <hillclimbing.h>


int main()
{
    string instFolder = "../order-scheduling-problem/instances/big/";
    string instName   = "bt_0.2_0.2_0001";

    const Instance instance(instFolder + instName);
//    cout << instance.toString() << endl;

    HillClimbing hc(instance);

    hc.run();

    cout << "Solution value: " << hc.getSolutionValue() << endl;
    cout << "Elapsed time:   " << hc.getElapsedTime() << " seconds" << endl;
    return 0;
}
