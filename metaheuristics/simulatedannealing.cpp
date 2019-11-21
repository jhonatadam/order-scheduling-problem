#include "simulatedannealing.h"

SimulatedAnnealing::SimulatedAnnealing(double initialProb, double endProb,
                                       double worsening, unsigned iterations, const Instance *inst) :
    OptimizationMethod(inst), initialProb(initialProb), endProb(endProb),
    worsening(worsening), iterations(iterations)
{

}

void SimulatedAnnealing::_run()
{
//        VND vnd = new VND(os);
//        vnd.run(bestSol);

    Solution current(solution.getInstance());

    double iniTemp = solution.getValue() * (worsening / log(1. / initialProb));
    double endTemp = solution.getValue() * (worsening / log(1. / endProb));

    size_t pertPerIte = solution.getNumOfSlots() * solution.getNumOfSlots() / 2;
    double lambda = pow(endTemp / iniTemp, 1.0 / iterations);
    double temp = iniTemp;

    // random generator
    long seed = 0; // chrono::system_clock::now().time_since_epoch().count();
    default_random_engine randGenerator(seed);
    uniform_int_distribution<size_t> randSlot(0, solution.getNumOfSlots() - 1);
    std::uniform_real_distribution<double> realDist(0.0, 1.0);

    for (unsigned it = 0; it < iterations; it++) {
        for (unsigned p = 0; p < pertPerIte; p++) {
            size_t slotA =  randSlot(randGenerator);
            size_t slotB =  randSlot(randGenerator);
            int delta = current.swapGain(slotA, slotB);

            if (delta < 0) {
                current.swap(slotA, slotB);
                if (current.getValue() < solution.getValue()) {
                    solution.copy(current);
                    cout << it << ", " << temp << ", " << solution.getValue() << endl;
                }
            } else if ( realDist(randGenerator) < (1. / exp(delta / temp)) ) {
                current.swap(slotA, slotB);
            }
        }
        temp *= lambda;
    }

    HillClimbing hc(solution);
    hc._run();
    solution.copy(hc.getSolution());
    cout << "HC: " << solution.getValue() << endl;
}
