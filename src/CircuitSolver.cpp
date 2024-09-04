#include "CircuitSolver.hpp"

namespace RLC_SOLVER {

    // Finds impedence from start node and every node in between to the end node.
    // Assumes there is a directed graph of nodes connected by components from the start node to the end node.
    std::string CircuitSolver::findImpedences(const NodePtr& aNode, const NodePtr& anEndNode) {
        if (!aNode->impedence.has_value()) {
            if (aNode->connections.size() > 1) {
                std::string theParallelSum;
                bool theFirst{true}; // Performance Optimization
                for (const auto& theComponent : aNode->connections) {
                    std::string theRecursiveImpedence;
                    if (theComponent->nextNode == anEndNode) {
                        theRecursiveImpedence = "0"; // Performance Optimization
                    } else {
                        theRecursiveImpedence = findImpedences(theComponent->nextNode, anEndNode);
                    }
                    if (!theFirst) theParallelSum += " + ";
                    if (theRecursiveImpedence != "0") {
                        theParallelSum += "1/(" + theComponent->getImpedence() + " + " + theRecursiveImpedence + ")"; // Parallel
                    } else {
                        theParallelSum += "1/(" + theComponent->getImpedence() + ")"; // Parallel
                    }
                    theFirst = false;
                }
                aNode->impedence = "1 / (" + theParallelSum + ")";
            } else { // (aNode->connections.size() == 1)
                const auto& theComponent{aNode->connections[0]};
                if (theComponent->nextNode == anEndNode) {
                    aNode->impedence = theComponent->getImpedence(); // Serial
                } else {
                    aNode->impedence = theComponent->getImpedence() + " + " + findImpedences(theComponent->nextNode, anEndNode); // Serial
                }
            }
        }
        return aNode->impedence.value();
    }

    // This assumes aStartNode is the node connected to V+ on the voltage source.
    void CircuitSolver::findVoltages(const NodePtr& aStartNode, const NodePtr& anEndNode, const std::vector<NodePtr>& aNodeList) {
        for (const NodePtr& theNode : aNodeList) {
            if (theNode == aStartNode) theNode->voltage = aStartNode->getSource(); // Performance Optimization
            else if (theNode == anEndNode) theNode->voltage = "0"; // Performance Optimization
            else theNode->voltage = aStartNode->getSource() + " * (" + theNode->impedence.value() + ") / (" + aStartNode->impedence.value() + ")"; // Voltage Divider
        }
    }

    void CircuitSolver::findCurrents(const std::vector<NodePtr>& aNodeList) {
        for (const NodePtr& theNode : aNodeList) {
            for (const auto& theComponent : theNode->connections) {
                theComponent->current = "(" + theNode->getVoltage() + " - " + theComponent->nextNode->getVoltage() + ")/" + theComponent->getImpedence(); // Ohm's Law: I = V/R
            }
        }
    }
    ///////////////////////////////////////////////////////// [README!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!] /////////////////////////////////////
    /* Note: this will work for Voltage Sources, but for Current Sources the order has to flip:
    *                                                           // UPDATE: No it doesn't!!!
    findImpedences()
    findCurrents() // Current Divider
    findVoltages() // Ohm's Law: V = I * R

    // So we need an if statement, and Circuit needs an enum for voltage source
    */
    Circuit CircuitSolver::solve(const std::vector<Circuit>& aCircuits) {
        for (auto& theCircuit : aCircuits) {
            findImpedences(theCircuit.startNode, theCircuit.endNode);
            findVoltages(theCircuit.startNode, theCircuit.endNode, theCircuit.nodeList);
            findCurrents(theCircuit.nodeList);
        }
         // TODO: Combine all nodes using superposition for multiple voltage sources (Add all voltages for all nodes, add all currents for all componentes together, according to matching names)
        return aCircuits[0]; // DEBUG // TODO: returns only the first solution
    }

}