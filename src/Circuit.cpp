#include <iostream>
#include "../dependencies/json.hpp"
#include "Circuit.hpp"

namespace RLC_SOLVER {
    
    Circuit::Circuit(const std::vector<NodePtr>& aNodeList, const NodePtr& aStartNode, const NodePtr& anEndNode, const std::vector<ComponentPtr>& aComponentList) :
            nodeList{aNodeList}, startNode{aStartNode}, endNode{anEndNode}, componentList{aComponentList} {}

    /* Example:
        {
          "Circuit": {
            "Nodes": {
              "node1": "voltageEquation1",
              "node2": "voltageEquation2",
              "node3": "voltageEquation3"
            },
            "Components": {
              "component1": "valueA",
              "component2": "valueB"
            }
          }
        }
    */
    std::string Circuit::toJSON() {
        std::string theJSONCircuit{"{\"Circuit\":{\"Nodes\":{"};
        for (size_t i = 0; i < nodeList.size(); i++) {
            theJSONCircuit += "\"" + nodeList[i]->getName() + "\":\"" + nodeList[i]->voltage + "\"";
            if (i + 1 < nodeList.size()) theJSONCircuit += ",";
        }
        theJSONCircuit += "},\"Components\":{";
        for (size_t i = 0; i < componentList.size(); i++) {
            theJSONCircuit += "\"" + componentList[i]->getName() + "\":\"" + componentList[i]->current + "\"";
            if (i + 1 < nodeList.size()) theJSONCircuit += ",";
        }
        theJSONCircuit += "}}}";
        return theJSONCircuit;
    }

    /* Example:
    {
      "Circuit": {
        "Nodes": {
          "node_426320887": [
            {
              "resistor_1065524102": "node_1376094319"
            }
          ],
          "node_1376094319": [
            {
              "resistor_1065524102": "node_426320887"
            },
            {
              "capacitor_527297228": "node_2114880340"
            }
          ],
          "node_2114880340": [
            {
              "capacitor_527297228": "node_1376094319"
            }
          ]
        },
        "Sources": [
          {
            "source-voltage_1332204801": {
              "VDD": "node_426320887",
              "GND": "node_1300216332"
            }
          },
          {
            "source-voltage_534814224": {
              "VDD": "node_2114880340",
              "GND": "node_1300216332"
            }
          }
        ]
      }
    }
    */
    std::vector<Circuit> Circuit::fromJSON(const std::string& aJsonData) {
        // Parse JSON
        auto theJson = nlohmann::json::parse(aJsonData);

        // Map to store node name to NodePtr
        std::unordered_map<std::string, NodePtr> theNodes;

        // Create NodePtr for each node in JSON and store in the map
        for (auto& theElement : theJson["Circuit"]["Nodes"].items()) {
            theNodes[theElement.key()] = std::make_shared<Node>(theElement.key());
        }

        // Set up connections between nodes
        for (auto& theElement : theJson["Circuit"]["Nodes"].items()) {
            NodePtr theNode = theNodes[theElement.key()];
            for (auto& theComponentArray : theElement.value()) {
                for (auto& theComponentElement : theComponentArray.items()) {
                    std::string theComponentName = theComponentElement.key();
                    std::string theConnectedNodeName = theComponentElement.value();
                    theNode->connections.push_back(std::make_shared<Component>(theComponentName, theNodes[theConnectedNodeName]));
                }
            }
        }

        // Handle voltage sources
        std::vector<std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>>> theSources;
        for (auto& theSourcesElement : theJson["Circuit"]["Sources"]) {
            for (auto& theSource : theSourcesElement.items()) {
                NodePtr theVddNode = theNodes[theSource.value()["VDD"]];
                theVddNode->voltage = theSource.key();
                NodePtr theGNDNode = theNodes[theSource.value()["GND"]];
                theSources.push_back({theVddNode, theGNDNode});
            }
        }

        std::vector<NodePtr> theNodeVector;
        for (const auto& [theNodeName, theNode] : theNodes) {
            theNodeVector.push_back(theNode);
        }

        std::vector<Circuit> theCircuitVector;
        for (const auto& [theStartNode, theEndNode] : theSources) {
            theCircuitVector.emplace_back(theNodeVector, theStartNode, theEndNode);
        }

        return theCircuitVector;
    }

}