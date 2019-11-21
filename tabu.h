#ifndef TABU_H
#define TABU_H

#include <list>
#include <unordered_map>

#include <solution.h>


struct TabuTree {
    struct Node {
        unordered_map<unsigned, Node*> children;
        ~Node() {
            for (auto it : children)
                delete it.second;
        }
    };

    Node root;

    void insert(Solution &sol, Node *node, unsigned slot = 0) {
        if (slot < sol.getNumOfSlots()) {
            auto it = node->children.find(sol.getOrder(slot));
            if (it != node->children.end()) {
                this->insert(sol, it->second, slot+1);
            } else {
                Node *newNode = new Node;
                node->children[sol.getOrder(slot)] = newNode;
                this->insert(sol, newNode, slot+1);
            }
        }
    }

    bool contains(Solution &sol, Node *node, unsigned slot = 0){
        if (sol.getNumOfSlots() == slot)
            return true;

        auto it = node->children.find(sol.getOrder(slot));
        if (it != node->children.end())
            return contains(sol, it->second, slot + 1);
        return false;
    }

    bool erase(Solution &sol, Node *node, unsigned slot = 0){
        if (sol.getNumOfSlots() == slot)
            return true;

        auto it = node->children.find(sol.getOrder(slot));
        if (it != node->children.end()) {
            if(erase(sol, it->second, slot + 1)) {
                if (node->children.size() == 1) {
                    if (node == &root) {
                        delete it->second;
                        node->children.erase(it);
                    }
                    return true;
                }

                delete it->second;
                node->children.erase(it);
            }
        }
        return false;
    }

    void clean(){
        for (auto it : root.children)
            delete it.second;
    }
};


class Tabu
{
    unsigned tenure;
    list<unsigned*> tabu;
    TabuTree tt;

public:
    Tabu(const unsigned tenure);

    // Element access
    bool contains(Solution &sol);

    // modifiers
    void insert(Solution &sol);
    void clean();
};

#endif // TABU_H
