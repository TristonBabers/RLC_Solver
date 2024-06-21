#ifndef CircuitSolver_hpp
#define CircuitSolver_hpp

namespace RLC_SOLVER {

    class CircuitSolver {
    public:
        CircuitSolver() {}
        virtual Circuit solve() {}
        virtual void JSON() {}

        // Finds impedence from start node and every node in between to the end node.
        // Assumes there is a directed graph of nodes connected by components from the start node to the end node.
        Complex findImpedences(const NodePtr& aNode, const NodePtr& anEndNode) {
            if (aNode == anEndNode) aNode->impedence = 0;
            if (aNode->impedence.has_value()) return aNode->impedence.value();
            if (aNode->connections.size() > 1) {
                Complex theParallelSum{0};
                for (const auto& theComponent : aNode->connections) {
                    theParallelSum += Complex{1} / (theComponent->getImpedence() + findImpedences(theComponent->nextNode, anEndNode)); // Parallel
                }
                aNode->impedence = Complex{1} / theParallelSum;
            } else { // (aNode->connections.size() == 1)
                const auto& theComponent{aNode->connections[0]};
                if (theComponent->nextNode == anEndNode) {
                    aNode->impedence = theComponent->getImpedence(); // Serial
                } else {
                    aNode->impedence = theComponent->getImpedence() + findImpedences(theComponent->nextNode, anEndNode);  // Serial
                }
            }
            return aNode->impedence.value();
        }

    

        // This assumes aStartNode is the node connected to V+ on the voltage source.
        void findVoltagesAndCurrents(const NodePtr& aStartNode, const std::vector<NodePtr>& aNodeList) {
            for (const NodePtr& theNode : aNodeList) {
                theNode->voltage = Complex{aStartNode->voltage * (theNode->impedence.value() / aStartNode->impedence.value())}.real(); // Voltage Divider // DEBUG only get real part for now.
            }
        }

        void solve(std::vector<Circuit>& aCircuits) {
            for (theCircuit : aCircuits) {
                findImpedences(aCircuit.startNode, aCircuit.endNode);
                findVoltagesAndCurrents(aCircuit.startNode, aCircuit.nodeList);
            }
        }
        std::vector<Circuit>;
    };

}

#endif /* CircuitSolver_hpp */