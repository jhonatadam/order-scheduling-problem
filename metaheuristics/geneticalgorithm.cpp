#include "geneticalgorithm.h"

void GeneticAlgorithm::initPopulation(vector<Solution *> &pop)
{
    for (unsigned i = 0; i < popSize; i++) {
        pop[i] = new Solution(solution.getInstance());
        pop[i]->shuffle(this->generator);
    }
}

void GeneticAlgorithm::selectParents(vector<Solution *> &source, vector<Solution *> &selected)
{   
    for (unsigned i = 0; i < selected.size(); i++) {
        std::uniform_int_distribution<size_t> dist(0, source.size() - 1);
        size_t s = dist(generator);
        for (unsigned j = 1; j < this->k; j++) {
            size_t x = dist(generator);
            if (source[x] < source[s])
                s = x;
        }

        selected[i] = source[s];
        source.erase(source.begin() + unsigned(s));
    }
}

Solution *GeneticAlgorithm::mutate(Solution *s)
{
    std::uniform_int_distribution<size_t> dist(0, solution.getNumOfSlots() - 1);
    size_t a = dist(generator);
    size_t b = dist(generator);

    while (a == b)
        b = dist(generator);
    Solution *m = new Solution(solution.getInstance());
    m->copy(*s);
    m->swap(a, b);
    return m;
}

bool GeneticAlgorithm::exists(vector<Solution *> &vector, Solution *s)
{
    for (Solution* i : vector) {
        if (i->operator==(*s))
            return true;
    }
    return false;
}

Solution *GeneticAlgorithm::OX(Solution *s1, Solution *s2)
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

    Solution *son = new Solution(solution.getInstance());
    son->setScheduling(newScheduling);
    return son;
}

Solution *GeneticAlgorithm::randomX(Solution *s1, Solution *s2, double x)
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

    Solution *son = new Solution(solution.getInstance());
    son->setScheduling(newScheduling);

    return son;
}

GeneticAlgorithm::GeneticAlgorithm(unsigned iterations, unsigned popSize, unsigned k,
                                   double mutateRate, double crossRate, const Instance *inst) :
    OptimizationMethod(inst), iterations(iterations), popSize(popSize),
    k(k), crossRate(crossRate), mutateRate(mutateRate)
{
    unsigned long seed = 0;//chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);
}

void GeneticAlgorithm::_run()
{
//    in = new boolean[os.N];
    vector<Solution*> pop(popSize, nullptr);
    vector<Solution*> parents(unsigned(crossRate * popSize), nullptr);
    initPopulation(pop);
    uniform_real_distribution<double> dist(0.0, 1.0);
    auto compFunc = [] (Solution *a, Solution *b) -> bool {return a->getValue() < b->getValue();};

    for (unsigned it = 0; it < iterations; it++) {
        selectParents(pop, parents);
        Solution *f;
        size_t len = parents.size();

        for (size_t i = 0; i < len; i++) {

            if (dist(generator) < this->mutateRate) {
                f = mutate(parents[i]);
//                if (!exists(parents, f) && !exists(pop, f)) {
                    parents.push_back(f);
//                } else {
//                    delete f;

//                }
            }


            for (size_t j = i + 1; j < len; j++) {
                f = OX(parents[i], parents[j]);
                if (!exists(parents, f) && !exists(pop, f)) {
                    parents.push_back(f);
                } else {
                    delete f;
                }

                f = OX(parents[j], parents[i]);

                if (!exists(parents, f) && !exists(pop, f)) {
                    parents.push_back(f);
                } else{
                    delete f;
                }

                f = randomX(parents[i], parents[j], .5);
                if (!exists(parents, f) && !exists(pop, f)) {
                    parents.push_back(f);
                } else{
                    delete f;
                }

                f = randomX(parents[j], parents[i], .5);
                if (!exists(parents, f) && !exists(pop, f)) {
                    parents.push_back(f);
                } else{
                    delete f;
                }
            }
        }


        // obtendo melhor solucao
        sort(parents.begin(), parents.end(), compFunc);
        Solution *best = parents[0];
        for (Solution* s : pop)
            if (s->getValue() < best->getValue())
                best = s;

        if (best->getValue() < solution.getValue()) {
            solution.copy(*best);
            cout << it << " " << solution.getValue() << endl;
        }

        // pegando elementos aleatrorios para preencher a proxima geracao
        if (parents.size() < popSize) {
            shuffle(pop.begin(), pop.end(), generator);
            while (parents.size() < popSize) {
                parents.push_back(pop.back());
                pop.pop_back();
            }
        }
        // deletando elementos da geracao anterior que nao sobreviveram
        for (Solution *s : pop)
            delete s;
        pop.clear();
        // deletando pais que nao sobrevivem para a proxima geracao
        for (size_t i = popSize; i < parents.size(); i++) {
            delete parents[i];
        }

        // nova populacao
        pop.assign(parents.begin(), parents.begin() + popSize);
        parents.resize(unsigned(crossRate * popSize));
        // pool.addAll(parents.subList(popSize, parents.size()));
    }

    for (Solution *s : pop)
        delete s;
}
