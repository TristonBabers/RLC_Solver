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
*/