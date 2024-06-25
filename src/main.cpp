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
        Circuit theResult{CircuitSolver::solve(std::vector<Circuit>{makeVoltageDividerCircuit()})};
        std::string formatted{formatJson(theResult.toJSON())};
        std::cout << formatJson(theResult.toJSON());
    }

}

int main() {
    RLC_SOLVER::test();
    return 0;
}