// Broken, saving code for eventual testing

/*
#include <iostream>
#include <unordered_map>
#include <iomanip>
#include <vector>

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

    Circuit makeVoltageDividerUnDaggedCircuit() {
        // Initialize Nodes
        NodePtr startNode{std::make_shared<Node>("START")};
        NodePtr endNode{std::make_shared<Node>("END", "0")}; // REQUIRED: set endnode impedence!!!
        NodePtr nodeB{std::make_shared<Node>("B")};
        
        // Initialize Components
        ComponentPtr r1{std::make_shared<Component>("R1", nodeB)};
        ComponentPtr r1_reverse{std::make_shared<Component>("R1", startNode)};
        ComponentPtr r2{std::make_shared<Component>("R2", endNode)};
        ComponentPtr r2_reverse{std::make_shared<Component>("R2", nodeB)};
        
        // Connect Circuit
        startNode->connections = std::vector<ComponentPtr>({r1});
        nodeB->connections = std::vector<ComponentPtr>({r2, r1_reverse});
        endNode->connections = std::vector<ComponentPtr>({r2_reverse});
        
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
        //Circuit theResult{CircuitSolver::solve(std::vector<Circuit>{makeParallelComboCircuit()})};
        Circuit theResult{CircuitSolver::solve(std::vector<Circuit>{makeVoltageDividerCircuit()})};

        //Circuit theCircuit{circuitFromJSON()};
        std::cout << formatJson(theResult.toJSON());

        Circuit theTemp{makeVoltageDividerUnDaggedCircuit()};
        Dagifier::dagify(theTemp);
        Circuit theOtherResult{CircuitSolver::solve(std::vector<Circuit>{theTemp})};

        //std::string formatted{formatJson(theResult.toJSON())};
        std::cout << formatJson(theOtherResult.toJSON());
    }
*/