#include "solution.h"


void Solution::updateValue(size_t begin, size_t end)
{
    if (begin == end)
        return;

    int prevEndAccTardiness = int(tardinessAcc[end]);

    for (size_t slot = begin; slot <= end; slot++) {
        unsigned order = scheduling[slot];
        unsigned maxTime = 0;
        for (size_t machine = 0; machine < instance.numberOfMachines; machine++) {
            timeAcc[slot][machine] = slot > 0 ? timeAcc[slot - 1][machine] : 0;
            timeAcc[slot][machine] += instance.orderMachine[order][machine];

            if (timeAcc[slot][machine] > maxTime)
                maxTime = timeAcc[slot][machine];
        }
        // updating tardiness accumulated
        tardinessAcc[slot] = slot > 0 ? tardinessAcc[slot - 1] : 0;
        tardinessAcc[slot] += maxTime > instance.dueDates[order] ? maxTime - instance.dueDates[order] : 0;
    }

    int endDiff = int(tardinessAcc[end]) - prevEndAccTardiness;
    for (size_t slot = end + 1; slot < scheduling.size(); slot++) {
        tardinessAcc[slot] = unsigned(int(tardinessAcc[slot]) + endDiff);
    }
}

int Solution::valueGain(size_t begin, size_t end)
{
    unsigned tempAcc = 0;
    vector<unsigned> tempTimeAcc(instance.numberOfMachines, 0);

    if (begin > 0) {
        tempAcc = tardinessAcc[begin - 1];
        for (size_t machine = 0; machine < instance.numberOfMachines; machine++)
            tempTimeAcc[machine] = timeAcc[begin - 1][machine];
    }

    for (size_t slot = begin; slot <= end; slot++) {
        unsigned order = scheduling[slot];
        unsigned maxTime = 0;
        for (size_t machine = 0; machine < instance.numberOfMachines; machine++) {
            tempTimeAcc[machine] += instance.orderMachine[order][machine];

            if (tempTimeAcc[machine] > maxTime)
                maxTime = tempTimeAcc[machine];
        }
        // updating accumulated tardiness
        if (maxTime > instance.dueDates[order])
            tempAcc += maxTime - instance.dueDates[order];
    }

    return int(tempAcc) - int(tardinessAcc[end]);
}

Solution::Solution(const Instance &instance) :
    instance(instance), scheduling(instance.numberOfOrders),
    timeAcc(instance.numberOfOrders, vector<unsigned>(instance.numberOfMachines)),
    tardinessAcc(instance.numberOfOrders)
{
    for (unsigned slot = 0; slot < instance.numberOfOrders; slot++) {
        scheduling[slot] = slot;
    }

    updateValue(0, instance.numberOfOrders - 1);
}

void Solution::swap(size_t slotA, size_t slotB)
{
    if (slotA == slotB)
        return;

    unsigned aux = scheduling[slotA];
    scheduling[slotA] = scheduling[slotB];
    scheduling[slotB] = aux;

    updateValue(min(slotA, slotB), max(slotA, slotB));
}

int Solution::swapGain(size_t slotA, size_t slotB)
{
    if (slotA == slotB)
        return 0;

    unsigned aux = scheduling[slotA];
    scheduling[slotA] = scheduling[slotB];
    scheduling[slotB] = aux;

    int gain = valueGain(min(slotA, slotB), max(slotA, slotB));

    aux = scheduling[slotA];
    scheduling[slotA] = scheduling[slotB];
    scheduling[slotB] = aux;

    return gain;
}

void Solution::shift(size_t from, size_t to)
{
    if (from == to)
        return;

    unsigned order = scheduling[from];

    if (from < to) {
        for (size_t slot = from; slot < to; slot++) {
            scheduling[slot] = scheduling[slot + 1];
        }
    } else if (to < from) {
        for (size_t slot = from; slot > to; slot--) {
            scheduling[slot] = scheduling[slot - 1];
        }
    }

    scheduling[to] = order;

    updateValue(min(from, to), max(from, to));
}

void Solution::shuffle()
{
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(scheduling.begin(), scheduling.end(), std::default_random_engine(seed));

    updateValue(0, instance.numberOfOrders - 1);
}

void Solution::copy(const Solution &other)
{
    if (instance.numberOfOrders != other.scheduling.size()) {
        cerr << "Solution::copy: copied solution must be to the same instance" << endl;
        exit(0);
    }

    this->scheduling.assign(other.scheduling.begin(), other.scheduling.end());
    this->timeAcc.assign(other.timeAcc.begin(), other.timeAcc.end());
    this->tardinessAcc.assign(other.tardinessAcc.begin(), other.tardinessAcc.end());
}

void Solution::perturbBySwap(unsigned numberOfSwaps)
{
    // random generator
    long seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine randGenerator(seed);
    // uniform distribution between 0 and swapsPerPerturb
    std::uniform_int_distribution<size_t> randDistribution(0, instance.numberOfOrders - 1);

    size_t minSlot = instance.numberOfOrders - 1;
    size_t maxSlot = 0;

    for (unsigned i = 0; i < numberOfSwaps; i++) {
        size_t slotA =  randDistribution(randGenerator);
        size_t slotB =  randDistribution(randGenerator); //x + Utils.rd.nextInt(2 * W) - W;

        // swap
        unsigned aux = scheduling[slotA];
        scheduling[slotA] = scheduling[slotB];
        scheduling[slotB] = aux;

        minSlot = min(minSlot, min(slotA, slotB));
        maxSlot = max(maxSlot, max(slotA, slotB));
    }

    updateValue(minSlot, maxSlot);
}

unsigned Solution::getValue()
{
    return tardinessAcc.back();
}

size_t Solution::getNumOfSlots() const
{
    return this->scheduling.size();
}

const Instance &Solution::getInstance() const
{
    return instance;
}

