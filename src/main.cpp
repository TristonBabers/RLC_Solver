/* Algorithm Description:
* 1. Create a graph of "routes" from the node around a voltage source to
* 
* 
* 
* Limitations:
* - Only works if there is a single voltage source
* --> Just use superposition on all other sources, and we're fine.
*/

#include <iostream>
#include <unordered_map>
#include <complex>
#include <optional>
#include <iomanip>
#include <memory>
#include <vector>

namespace RLC_SOLVER {

    using Complex = std::complex<float>;

    class Component; // Forward Declare

    class Node {
    public:
        Node(const std::string& aName, std::vector<std::unique_ptr<Component>> aConnections={}) :
                name(aName), connections{std::move(aConnections)}, impedence{std::nullopt}, voltage{0}, current{0} {}

        Node(const std::string& aName, float aVoltage, float aCurrent, std::vector<std::unique_ptr<Component>> aConnections={}) :
                name(aName), connections{std::move(aConnections)}, impedence{std::nullopt}, voltage{aVoltage}, current{aCurrent} {}

        bool operator==(const Node& anotherNode) const {
            return name == anotherNode.name;
        }

        std::string name;
        float voltage;
        float current;
        std::optional<Complex> impedence;
        std::vector<std::unique_ptr<Component>> connections;
    };

    using NodePtr = std::shared_ptr<Node>;

    class Component {
    public:
        Component(const NodePtr& aNode) : nextNode(aNode) {}

        virtual Complex getImpedence() const {
            return 9999;
        }

        virtual ~Component() = default;

        NodePtr nextNode;
    };

    class Resistor : public Component {
    public:
        Resistor(const NodePtr& aNode, float aResistance) : Component(aNode), resistance(aResistance) {}

        virtual Complex getImpedence() const override {
            return Complex{resistance};
        }

    protected:
        float resistance;
    };

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

    class Circuit {
    public:
        Circuit(const std::vector<NodePtr>& aNodeList, const NodePtr& aStartNode, const NodePtr& anEndNode) :
                nodeList{aNodeList}, startNode{aStartNode}, endNode{anEndNode} {}
        std::vector<NodePtr> nodeList;
        NodePtr startNode;
        NodePtr endNode;
    };

    // This assumes aStartNode is the node connected to V+ on the voltage source.
    void findVoltagesAndCurrents(const NodePtr& aStartNode, const std::vector<NodePtr>& aNodeList) {
        for (const NodePtr& theNode : aNodeList) {
            theNode->voltage = Complex{aStartNode->voltage * (theNode->impedence.value() / aStartNode->impedence.value())}.real(); // Voltage Divider // DEBUG only get real part for now.
        }
    }

    void solve(Circuit& aCircuit) {
        findImpedences(aCircuit.startNode, aCircuit.endNode);
        findVoltagesAndCurrents(aCircuit.startNode, aCircuit.nodeList);
    }

    Circuit makeVoltageDividerCircuit(float aVoltage, float aResistor1, float aResistor2) {
        // Start Node (Required)
        NodePtr startNode{std::make_shared<Node>("START", aVoltage, 0.0f)};

        // Initialize Nodes
        NodePtr endNode{std::make_shared<Node>("END")};
        NodePtr nodeB{std::make_shared<Node>("B")};

        // Connect Circuit
        startNode->connections.push_back(std::make_unique<Resistor>(nodeB, aResistor1));
        nodeB->connections.push_back(std::make_unique<Resistor>(endNode, aResistor2));

        // End Node (Required)
        endNode->impedence = 0;
        endNode->voltage = 0;
        
        // Solve Circuit
        std::vector<NodePtr> theNodeList{startNode, nodeB, endNode};
        return Circuit{theNodeList, startNode, endNode};
    }

    bool testVoltageDividerCircuit(float aVoltage, float aResistor1, float aResistor2) {
        // Create Circuit
        Circuit theCircuit{makeVoltageDividerCircuit(aVoltage, aResistor1, aResistor2)};
        solve(theCircuit);
        //Display
        std::cout << std::fixed << std::setprecision(2);
        std::cout << std::setw(15) << " " << "          ______/\\  /\\  /\\_____________/\\  /\\  /\\_________\n";
        std::cout << std::setw(15) << " " << "         |        \\/  \\/          |      \\/  \\/           |\n";
        std::cout << std::setw(15) << " " << "         |  R1 = " << std::setw(17) << std::left << std::to_string(aResistor1) + " ohms " << "| R2 = " << std::setw(17) << std::left << std::to_string(aResistor2) + " ohms" << std::setw(3) << std::left << "|\n";
        std::cout << std::setw(15) << " " << "  ______|______                  |                       |\n";
        std::cout << std::setw(15) << " " << "  /      +      \\                 |                       |\n";
        std::cout << std::setw(15) << " " << " /               \\                o                       |\n";
        std::cout << std::setw(15) << " " << "/  " << std::setw(15) << std::left << std::to_string(aVoltage) + " V " << std::setw(4) << std::left << "\\" << "      V(R2) = " << std::setw(22) << std::left << std::to_string(theCircuit.nodeList[1]->voltage) + " V " << "|\n";
        std::cout << std::setw(15) << " " << "\\                 /                                       |\n";
        std::cout << std::setw(15) << " " << " \\       -       /                                        |\n";
        std::cout << std::setw(15) << " " << "  \\_____________/                                         |\n";
        std::cout << std::setw(15) << " " << "         |                                                |\n";
        std::cout << std::setw(15) << " " << "         |                                                |\n";
        std::cout << std::setw(15) << " " << "         |________________________________________________|\n";

        
        return true;
    }
}
    int main() {
        using namespace RLC_SOLVER;
        //                        V    R1   R2
        testVoltageDividerCircuit(1200, 300, 100);
        return 0;
    }