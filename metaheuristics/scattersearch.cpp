#include "scattersearch.h"

unsigned ScatterSearch::getDistance(Solution *s1, Solution *s2)
{
    unsigned distance = 0;
    for (unsigned i = 0; i < s1->getNumOfSlots(); i++)
        if (s1->getScheduling()[i] != s2->getScheduling()[i])
            distance++;
    return distance;
}

void ScatterSearch::initPopulation(vector<Solution *> &population)
{
    cout << "Initializing population..." << endl;
    LaterOnFirst lf(30, solution.getInstance());
    MinDueDateHeuristic mdd(30, solution.getInstance());
    vector<unsigned> scheduling(solution.getNumOfSlots());
    iota(scheduling.begin(), scheduling.end(), 0);

    for (unsigned i = 0; i < this->popIniSize; i++) {
        if (i < (popIniSize/3)) {
            lf._run();
            population[i] = new Solution(solution.getInstance());
            population[i]->copy(lf.getSolution());
        } else if (i > (popIniSize/3) * 2) {
            mdd._run();
            population[i] = new Solution(solution.getInstance());
            population[i]->copy(mdd.getSolution());
        } else {
            shuffle(scheduling.begin(), scheduling.end(), generator);
            population[i] = new Solution(solution.getInstance());
            population[i]->setScheduling(scheduling);
        }

        if (i % 100 == 0)
            cout << 100.*(double(i)/this->popIniSize) << "%" <<  endl;
    }
}

void ScatterSearch::selectElite(vector<Solution*> &population, vector<Solution*> &elite)
{
    unsigned pivot = 0;
    unsigned bestCost = population.front()->getValue();
    for (unsigned i = 1; i < population.size(); i++) {
        if (population[i]->getValue() < bestCost) {
            pivot = i;
            bestCost = population[i]->getValue();
        }
    }

    elite[0] = population[pivot];
    vector<bool> in(population.size());
    in[pivot] = true;
    unsigned distances[population.size()];
    for (unsigned i = 0; i < population.size(); i++) {
        distances[i] = getDistance(elite.front(), population[i]);
    }

    for (unsigned k = 1; k < eliteSize; k++) {
        // choosing a new elite memeber
        pivot = 0;
        unsigned max = 0;
        for (unsigned i = 0; i < population.size(); i++) {
            if (!in[i] && max < distances[i]) {
                pivot = i;
                max = distances[i];
            }
        }
        elite[k] = population[pivot];
        in[pivot] = true;



        // updating distances to elite
        for (unsigned i = 0; i < population.size(); i++) {
            if (!in[i]) {
                distances[i] = min(getDistance(elite[k], population[i]), distances[i]);
            }
        }
    }

    for (unsigned i = 0; i < population.size(); i++)
        if (!in[i])
            delete population[i];
}

void ScatterSearch::OX(Solution *&son, Solution* s1, Solution* s2)
{
    const size_t half = solution.getNumOfSlots() / 2;
    uniform_int_distribution<size_t> dist(0, half);
    size_t a = dist(generator);
    size_t b = a + half;

    vector<unsigned> newScheduling(solution.getNumOfSlots());
    vector<bool> in(solution.getNumOfSlots(), false);

    for (size_t i = a; i < b; i++) {
        newScheduling[i] = s1->getOrder(i);
        in[s1->getOrder(i)] = true;
    }


    b = b % solution.getNumOfSlots();
    for (size_t i = 0, s2Slot = b, sonSlot = b, len = solution.getNumOfSlots() - half; i < len;) {
        if (!in[s2->getOrder(s2Slot)]) {
            newScheduling[sonSlot] = s2->getOrder(s2Slot);
            sonSlot++;
            if (sonSlot >= solution.getNumOfSlots())
                sonSlot = 0;
            i++;
        }
        s2Slot++;
        if (s2Slot >= solution.getNumOfSlots())
            s2Slot = 0;
    }

    if (son == nullptr)
        son = new Solution(solution.getInstance());
    son->setScheduling(newScheduling);
}

void ScatterSearch::randomX(Solution*& son, Solution *s1, Solution *s2, double x)
{
    vector<unsigned> newScheduling(solution.getNumOfSlots(), numeric_limits<unsigned>::max());
    vector<bool> in(solution.getNumOfSlots(), false);
    uniform_real_distribution<double> dist(0.0, 1.0);

    size_t len = solution.getNumOfSlots();
    for (unsigned i = 0; i < solution.getNumOfSlots(); i++) {
        if (dist(generator) < x) {
            newScheduling[i] = s1->getOrder(i);
            in[s1->getOrder(i)] = true;
            len--;
        }
    }

    for (unsigned i = 0, j = 0, k = 0; i < len; i++) {
        while (newScheduling[j] < numeric_limits<unsigned>::max()) j++;
        while (in[s2->getOrder(k)]) k++;
        newScheduling[j++] = s2->getOrder(k++);
    }


    if (son == nullptr)
        son = new Solution(solution.getInstance());
    son->setScheduling(newScheduling);
}

void ScatterSearch::pathRelinking(Solution *&son, Solution *s1, Solution *s2)
{
    vector<unsigned> bestScheduling;
    bestScheduling.assign(s1->getScheduling().begin(), s1->getScheduling().end());
    unsigned bestValue = numeric_limits<unsigned>::max();
    if (son == nullptr)
        son = new Solution(solution.getInstance());
    son->copy(*s1);

    for (unsigned i = 0; i < son->getNumOfSlots(); i++) {
        if (son->getOrder(i) != s2->getOrder(i)) {
            son->swap(i, son->getSlot(s2->getOrder(i)));
            if (son->getValue() < bestValue) {
                if (equal(son->getScheduling().begin() + i, son->getScheduling().end(), s2->getScheduling().begin() + i))
                    break;
                bestValue = son->getValue();
                bestScheduling.assign(son->getScheduling().begin(), son->getScheduling().end());
            }
        }
    }

    son->setScheduling(bestScheduling);
}

ScatterSearch::ScatterSearch(unsigned iterations, unsigned popIniSize,
                             unsigned eliteSize, const Instance* inst):
    OptimizationMethod(inst), iterations(iterations),
    popIniSize(popIniSize), eliteSize(eliteSize)
{

}

void ScatterSearch::_run()
{
    // initializing data
    vector<double> score(solution.getNumOfSlots());
    auto compFunc = [] (Solution *a, Solution *b) -> bool {return a->getValue() < b->getValue();};

    vector<Solution*> population(popIniSize, nullptr);
    initPopulation(population);

    vector<Solution*> elite(eliteSize, nullptr);
    selectElite(population, elite);

//    cout << "Improving elite.." << endl;
//    HillClimbing hc(solution.getInstance());
//    for (unsigned i = 0; i < elite.size(); i++) {
//        hc.getSolution().copy(*elite[i]);
//        hc._run();
//        elite[i]->copy(hc.getSolution());

//        if (i % 10 == 0)
//            cout << 100.*(double(i)/eliteSize) << "%" <<  endl;
//    }

    if (elite.front()->getValue() < solution.getValue())
        solution.copy(*elite.front());
    cout << "- " << solution.getValue() << endl;

    make_heap(elite.begin(), elite.end(), compFunc);

    size_t newGenSize = 0;
    vector<Solution*> newGen(2 * elite.size() * elite.size(), nullptr);
    for (unsigned it = 0; it < iterations; it++) {
        // generating new population
        for (size_t i = 0; i < elite.size(); i++) {
            for (size_t j = 0; j < eliteSize; j++) {
                if (i != j) {
//                    OX(newGen[newGenSize++], elite[i], elite[j]);
                    randomX(newGen[newGenSize++], elite[i], elite[j], 0.5);
                    if (getDistance(elite[i], elite[j]) > 10)
                        pathRelinking(newGen[newGenSize++], elite[i], elite[j]);
                }
            }
        }

        for (unsigned i = 0; i < newGenSize; i++) {
            if (newGen[i]->getValue() < elite.front()->getValue()) {
                // removing worst element
                pop_heap(elite.begin(), elite.end(), compFunc);
                // swaping
                Solution* temp = newGen[i];
                newGen[i] = elite.back();
                elite.back() = temp;
                // adding new element
                push_heap(elite.begin(), elite.end(), compFunc);
            }
        }

        Solution *best = &solution;
        for (Solution *s : elite)
            if (s->getValue() < best->getValue())
                best = s;
        if (best->getValue() < solution.getValue()) {
            solution.copy(*best);
            cout << it << " " << solution.getValue() << endl;
        }

        newGenSize = 0;
    }


    // cleaning memory
    for (Solution* s : elite)
        delete s;

    for (Solution* s : newGen)
        delete s;
}
