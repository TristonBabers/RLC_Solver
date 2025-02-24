#include <iostream>
#include <iomanip>
#include <vector>
#include "../dependencies/json.hpp"
#include "CircuitSolver.hpp"
#include "DAGifier.hpp"
#include <complex>
#include <stack>

#ifndef Tester_cpp
#define Tester_cpp

namespace RLC_SOLVER {

    using Complex = std::complex<double>;

    class Tester {
    public:
        Tester() {}

        /* Voltage Divider Circuit
        *    ________
        *   |        |
        *   |        R1
        *  (V)       |
        *   |        R2
        *   |________|
        *       |
        *      ---
        *       -
        */ 
        bool voltageDivider(std::stringstream &anOut) {
            try {
                std::string simpleCircuit{R"""(
                    {
                        "Circuit": {
                            "Nodes": {
                                "node_1": [
                                    { "Resistor_1": "node_2" }
                                ],
                                "node_2": [
                                    { "Resistor_1": "node_1" },
                                    { "Resistor_2": "node_3" }
                                ],
                                "node_3": [
                                    { "Resistor_2": "node_2" }
                                ]
                            },
                            "Sources": [
                                {
                                    "Voltage_Source_0": {
                                        "VDD": "node_1",
                                        "GND": "node_3"
                                    }
                                }
                            ]
                        }
                    }
                )"""};

                // Compact JSON
                simpleCircuit.erase(
                    std::remove_if(simpleCircuit.begin(), simpleCircuit.end(), [](unsigned char c) {
                        return std::isspace(c);
                    }),
                    simpleCircuit.end()
                );

                // Solve Circuit
                std::vector<Circuit> theCircuits{Circuit::fromJSON(simpleCircuit)};
                for (Circuit& theCircuit : theCircuits) {
                    Dagifier::dagify(theCircuit);
                }
                const Circuit theSolutionCircuit{CircuitSolver::solve(theCircuits)};

                // Replace Placeholders and Evaluate Expressions
                std::vector<std::pair<std::string, std::string>> theNodes;
                for (const auto& aNodePtr : theSolutionCircuit.nodeList) {
                    if (aNodePtr->impedence.has_value()) {
                        theNodes.push_back({aNodePtr->name, aNodePtr->impedence.value()});
                    }
                }
                std::unordered_map<std::string, double> theValues = {
                    {"Voltage_Source_0", 6.0},
                    {"Resistor_1", 10.0},
                    {"Resistor_2", 20.0},
                };
                std::vector<std::pair<std::string, Complex>> theResults;
                for (const auto& [theNodeName, theNode] : theNodes) {
                    std::string theUpdatedNode = replacePlaceholders(theNode, theValues);
                    Complex theResult = evaluateExpression(theUpdatedNode);
                    theResults.push_back({theNodeName, theResult});
                }

                // Output Results
                if (theResults.size() != 2) {
                    anOut << "Incorrect number of Results\n";
                    return false;
                } else if (theResults[0].second != Complex{30, 0} || theResults[1].second != Complex{20, 0}) {
                    anOut << theResults[0].first << ": " << theResults[0].second << "\n";
                    anOut << theResults[1].first << ": " << theResults[1].second << "\n";
                    return false;
                }
                return true;
            } catch (const std::exception& e) {
                anOut << e.what();
                return false;
            }
        }

        /* Simple Circuit
        *    ________
        *   |        |
        *  (V)       R1
        *   |________|
        *       |
        *      ---
        *       -
        */ 
        bool simpleCircuit(std::stringstream &anOut) {
            try {
                std::string simpleCircuit{R"""(
                    {
                        "Circuit": {
                            "Nodes": {
                                "node_1": [
                                    { "Resistor_1": "node_2" }
                                ],
                                "node_2": [
                                    { "Resistor_1": "node_1" }
                                ]
                            },
                            "Sources": [
                                {
                                    "Voltage_Source_0": {
                                        "VDD": "node_1",
                                        "GND": "node_2"
                                    }
                                }
                            ]
                        }
                    }
                )"""};

                // Compact JSON
                simpleCircuit.erase(
                    std::remove_if(simpleCircuit.begin(), simpleCircuit.end(), [](unsigned char c) {
                        return std::isspace(c);
                    }),
                    simpleCircuit.end()
                );

                // Solve Circuit
                std::vector<Circuit> theCircuits{Circuit::fromJSON(simpleCircuit)};
                for (Circuit& theCircuit : theCircuits) {
                    Dagifier::dagify(theCircuit);
                }
                const Circuit theSolutionCircuit{CircuitSolver::solve(theCircuits)};

                // Replace Placeholders and Evaluate Expressions
                std::vector<std::pair<std::string, std::string>> theNodes;
                for (const auto& aNodePtr : theSolutionCircuit.nodeList) {
                    if (aNodePtr->impedence.has_value()) {
                        theNodes.push_back({aNodePtr->name, aNodePtr->impedence.value()});
                    }
                }
                std::unordered_map<std::string, double> theValues = {
                    {"Voltage_Source_0", 5.0},
                    {"Resistor_1", 10.0},
                };
                std::vector<std::pair<std::string, Complex>> theResults;
                for (const auto& [theNodeName, theNode] : theNodes) {
                    std::string theUpdatedNode = replacePlaceholders(theNode, theValues);
                    Complex theResult = evaluateExpression(theUpdatedNode);
                    theResults.push_back({theNodeName, theResult});
                }

                // Output Results
                if (theResults.size() < 1) {
                    anOut << "No results\n";
                    return false;
                } else if (theResults[0].second != Complex{10, 0}) {
                    anOut << theResults[0].first << ": " << theResults[0].second << "\n";
                    return false;
                }
                return true;
            } catch (const std::exception& e) {
                anOut << e.what();
                return false;
            }
        }
        
        /* Advanced Circuit
        *    ____________
        *   |    |   |   |
        *   |    R1  R2  |
        *   |    |___|   |
        *  (V)     |     R3
        *   |     R4     |
        *   |      |     |
        *   |______|_____|
        *       |
        *      ---
        *       -
        */ 
        bool advancedCircuit(std::stringstream &anOut) {
            try {
                std::string advancedCircuit{R"""(
                    {
                        "Circuit": {
                            "Nodes": {
                                "node_1": [
                                    { "Resistor_1": "node_2" },
                                    { "Resistor_2": "node_2" },
                                    { "Resistor_3": "node_4" }
                                ],
                                "node_2": [
                                    { "Resistor_1": "node_1" },
                                    { "Resistor_2": "node_1" },
                                    { "Resistor_4": "node_4" }
                                ],
                                "node_4": [
                                    { "Resistor_3": "node_1" },
                                    { "Resistor_4": "node_2" }
                                ]
                            },
                            "Sources": [
                                {
                                    "Voltage_Source_0": {
                                        "VDD": "node_1",
                                        "GND": "node_4"
                                    }
                                }
                            ]
                        }
                    }
                )"""};

                // Compact JSON
                advancedCircuit.erase(
                    std::remove_if(advancedCircuit.begin(), advancedCircuit.end(), [](unsigned char c) {
                        return std::isspace(c);
                    }),
                    advancedCircuit.end()
                );

                // Solve Circuit
                std::vector<Circuit> theCircuits{Circuit::fromJSON(advancedCircuit)};
                for (Circuit& theCircuit : theCircuits) {
                    Dagifier::dagify(theCircuit);
                }
                const Circuit theSolutionCircuit{CircuitSolver::solve(theCircuits)};

                // Replace Placeholders and Evaluate Expressions
                std::vector<std::pair<std::string, std::string>> theNodes;
                for (const auto& aNodePtr : theSolutionCircuit.nodeList) {
                    if (aNodePtr->impedence.has_value()) {
                        theNodes.push_back({aNodePtr->name, aNodePtr->impedence.value()});
                    }
                }
                std::unordered_map<std::string, double> theValues = {
                    {"Voltage_Source_0", 5.0},
                    {"Resistor_1", 10.0},
                    {"Resistor_2", 20.0},
                    {"Resistor_3", 30.0},
                    {"Resistor_4", 40.0}
                };
                std::vector<std::pair<std::string, Complex>> theResults;
                for (const auto& [theNodeName, theNode] : theNodes) {
                    std::string theUpdatedNode = replacePlaceholders(theNode, theValues);
                    //std::cout << theUpdatedNode << "\n"; // DEBUG TODO: Actually test if this works (crashes before)
                    Complex theResult = evaluateExpression(theUpdatedNode);
                    theResults.push_back({theNodeName, theResult});
                }

                // Output Results
                for (size_t i = 0; i < theResults.size(); ++i) {
                    anOut << theResults[i].first << ": " << theResults[i].second << "\n";
                }
                return true;
            } catch (const std::exception& e) {
                anOut << e.what();
                return false;
            }
        }
    protected:
        std::string replacePlaceholders(std::string anExpression, const std::unordered_map<std::string, double>& aMapOfValues) {
            for (const auto& [key, value] : aMapOfValues) {
                std::string thePlaceholder = "{" + key + "}";
                size_t pos = 0;
                while ((pos = anExpression.find(thePlaceholder, pos)) != std::string::npos) {
                    anExpression.replace(pos, thePlaceholder.length(), std::to_string(value));
                    pos += std::to_string(value).length();
                }
            }
            return anExpression;
        }

        // Check if a character is an operator
        bool is_operator(char c) {
            return c == '+' || c == '-' || c == '*' || c == '/';
        }

        // Operator precedence
        int precedence(char op) {
            if (op == '+' || op == '-') return 1;
            if (op == '*' || op == '/') return 2;
            return 0;
        }

        // Convert infix expression to postfix using Shunting Yard Algorithm
        std::vector<std::string> infix_to_postfix(const std::string& expression) {
            std::stack<char> ops;
            std::vector<std::string> output;
            std::stringstream token;
            for (size_t i = 0; i < expression.length(); ++i) {
                char c = expression[i];
                if (isspace(c)) continue;
                // Handle numbers and complex literals
                if (isdigit(c) || c == '.' || c == 'i') {
                    token << c;
                } else {
                    if (!token.str().empty()) {
                        output.push_back(token.str());
                        token.str("");
                    }
                    if (is_operator(c)) {
                        while (!ops.empty() && precedence(ops.top()) >= precedence(c)) {
                            output.push_back(std::string(1, ops.top()));
                            ops.pop();
                        }
                        ops.push(c);
                    } else if (c == '(') {
                        ops.push(c);
                    } else if (c == ')') {
                        while (!ops.empty() && ops.top() != '(') {
                            output.push_back(std::string(1, ops.top()));
                            ops.pop();
                        }
                        ops.pop(); // Remove '('
                    }
                }
            }
            if (!token.str().empty()) {
                output.push_back(token.str());
            }
            while (!ops.empty()) {
                output.push_back(std::string(1, ops.top()));
                ops.pop();
            }
            return output;
        }

        // Evaluate a postfix (RPN) expression
        Complex evaluate_postfix(const std::vector<std::string>& postfix) {
            std::stack<Complex> eval_stack;
            for (const auto& token : postfix) {
                if (is_operator(token[0]) && token.length() == 1) {
                    Complex b = eval_stack.top(); eval_stack.pop();
                    Complex a = eval_stack.top(); eval_stack.pop();
                    switch (token[0]) {
                        case '+': eval_stack.push(a + b); break;
                        case '-': eval_stack.push(a - b); break;
                        case '*': eval_stack.push(a * b); break;
                        case '/': eval_stack.push(a / b); break;
                    }
                } else {
                    // Handle complex literals like "5i"
                    if (token.back() == 'i') {
                        double imag_value = std::stod(token.substr(0, token.size() - 1));
                        eval_stack.push(Complex(0.0, imag_value));
                    } else {
                        eval_stack.push(Complex(std::stod(token), 0.0));
                    }
                }
            }
            return eval_stack.top();
        }

        Complex evaluateExpression(const std::string& anExpression) {
            auto postfix = infix_to_postfix(anExpression);
            return evaluate_postfix(postfix);
        }
    };

}

#endif /* Tester_cpp */