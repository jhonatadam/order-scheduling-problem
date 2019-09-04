#include <hillclimbing.h>


int main()
{
    string instFolder = "../order-scheduling-problem/instances/small/";
    string instName   = "t_0.2_0.2_0001";

    const Instance instance(instFolder + instName);
    cout << instance.toString() << endl;

    HillClimbing hc(instance);

    hc.run();

    return 0;
}
