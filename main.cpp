#include <instance.h>


int main()
{
    string instFolder = "../OrderSchedulingProblem/instances/";
    string instName   = "01";

    Instance instance(instFolder + instName);

    cout << instance.toString() << endl;

    return 0;
}
