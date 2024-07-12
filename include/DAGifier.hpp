#ifndef Dagifier_hpp
#define Dagifier_hpp

#include "Circuit.hpp"
#include <string>
#include <optional>
#include <memory>

namespace RLC_SOLVER {

    class Dagifier {
    public:
        // Assumes that there are duplicated components across both connections of a pair connected nodes:
        // e.g.:  NodeA --[Resistor1]--> NodeB & NodeB --[Resistor1]--> NodeA.
        static bool dagify(Circuit& aCircuit) {
            // Run DFS from sink node and record pre and post orders
            size_t theClock{1};
            bool theDagificationWorked{true};
            explore(aCircuit.endNode, theClock);
            // For each edge keep the connection if the node it connects to has a lesser post order than the node it's connecting from.
            for (auto& theNode : aCircuit.nodeList) {
                theNode->connections.erase(std::remove_if(theNode->connections.begin(), theNode->connections.end(), [&theNode, &theDagificationWorked](ComponentPtr& aComponent) {
                    if (theNode->postOrder == 0 || aComponent->nextNode->postOrder == 0) { // A node was not visited via DFS from end node (Circuit might be incomplete)
                        theDagificationWorked = false;
                        return false;
                    } else if (theNode->postOrder > aComponent->nextNode->postOrder) {
                        return true;
                    } else {
                        return false;
                    }
                }), theNode->connections.end());
            }
            return theDagificationWorked;
        }
    protected:
        static void explore(const NodePtr& aNode, size_t& aClock) {
            aNode->visited = true;
            aNode->preOrder = aClock++;
            for (auto& theComponent : aNode->connections) {
                if (!theComponent->nextNode->visited) explore(theComponent->nextNode, aClock);
            }
            aNode->postOrder = aClock++;
        }
    };
}

#endif /* Dagifier_hpp */