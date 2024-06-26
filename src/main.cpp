/* Algorithm Description:
* 1. Create a graph of "routes" from the node around a voltage source to
* 
* 
* 
* Limitations:
* - Only works if there is a single voltage source
* --> Just use superposition on all other sources, and we're fine.
*/

#include "CircuitSolver.hpp"
#include <iostream>

namespace RLC_SOLVER {

    Circuit makeVoltageDividerCircuit() {
        // Initialize Nodes
        NodePtr startNode{std::make_shared<Node>("START")};
        NodePtr endNode{std::make_shared<Node>("END", "0")}; // REQUIRED: set endnode impedence!!!
        NodePtr nodeB{std::make_shared<Node>("B")};
        
        // Initialize Components
        ComponentPtr r1{std::make_shared<Component>("R1", nodeB)};
        ComponentPtr r2{std::make_shared<Component>("R2", endNode)};
        
        // Connect Circuit
        startNode->connections.push_back(r1);
        nodeB->connections.push_back(r2);
        
        // Solve Circuit
        std::vector<NodePtr> theNodeList{startNode, nodeB, endNode};
        std::vector<ComponentPtr> theComponentList{r1, r2};
        return Circuit{theNodeList, startNode, endNode, theComponentList};
    }

    Circuit makeTripleVoltageDividerCircuit() {
        // Initialize Nodes
        NodePtr startNode{std::make_shared<Node>("START")};
        NodePtr endNode{std::make_shared<Node>("END", "0")}; // REQUIRED: set endnode impedence!!!
        NodePtr nodeB{std::make_shared<Node>("B")};
        NodePtr nodeC{std::make_shared<Node>("C")};
        
        // Initialize Components
        ComponentPtr r1{std::make_shared<Component>("R1", nodeB)};
        ComponentPtr r2{std::make_shared<Component>("R2", nodeC)};
        ComponentPtr r3{std::make_shared<Component>("R3", endNode)};
        
        // Connect Circuit
        startNode->connections.push_back(r1);
        nodeB->connections.push_back(r2);
        nodeC->connections.push_back(r3);
        
        // Solve Circuit
        std::vector<NodePtr> theNodeList{startNode, nodeB, nodeC, endNode};
        std::vector<ComponentPtr> theComponentList{r1, r2, r3};
        return Circuit{theNodeList, startNode, endNode, theComponentList};
    }


    Circuit makeParallelComboCircuit() {
        // Initialize Nodes
        NodePtr startNode{std::make_shared<Node>("START")};
        NodePtr endNode{std::make_shared<Node>("END", "0")}; // REQUIRED: set endnode impedence!!!
        NodePtr nodeB{std::make_shared<Node>("B")};
        NodePtr nodeC{std::make_shared<Node>("C")};
        
        // Initialize Components
        ComponentPtr r1{std::make_shared<Component>("R1", nodeB)};
        ComponentPtr r2{std::make_shared<Component>("R2", nodeC)};
        ComponentPtr r3{std::make_shared<Component>("R3", endNode)};
        ComponentPtr r4{std::make_shared<Component>("R4", endNode)};
        
        // Connect Circuit
        startNode->connections.push_back(r1);
        nodeB->connections.push_back(r2);
        nodeB->connections.push_back(r4);
        nodeC->connections.push_back(r3);
        
        // Solve Circuit
        std::vector<NodePtr> theNodeList{startNode, nodeB, nodeC, endNode};
        std::vector<ComponentPtr> theComponentList{r1, r2, r3, r4};
        return Circuit{theNodeList, startNode, endNode, theComponentList};
    }

std::string formatJson(const std::string& compactJson) {
    std::string formattedJson;
    int level = 0;
    bool inQuotes = false;

    for (char ch : compactJson) {
        switch (ch) {
            case '{':
            case '[':
                formattedJson += ch;
                if (!inQuotes) {
                    level++;
                    formattedJson += '\n';
                    formattedJson += std::string(level, '\t');
                }
                break;
            case '}':
            case ']':
                if (!inQuotes) {
                    level--;
                    formattedJson += '\n';
                    formattedJson += std::string(level, '\t');
                }
                formattedJson += ch;
                break;
            case ',':
                formattedJson += ch;
                if (!inQuotes) {
                    formattedJson += '\n';
                    formattedJson += std::string(level, '\t');
                }
                break;
            case '"':
                formattedJson += ch;
                inQuotes = !inQuotes;
                break;
            default:
                formattedJson += ch;
                break;
        }
    }

    return formattedJson;
}

    void test() {
        //Circuit theResult{CircuitSolver::solve(std::vector<Circuit>{makeVoltageDividerCircuit()})};
        //Circuit theResult{CircuitSolver::solve(std::vector<Circuit>{makeTripleVoltageDividerCircuit()})};
        Circuit theResult{CircuitSolver::solve(std::vector<Circuit>{makeParallelComboCircuit()})};
        
        std::string formatted{formatJson(theResult.toJSON())};
        std::cout << formatJson(theResult.toJSON());
    }

}

int main() {
    RLC_SOLVER::test();
    return 0;
}