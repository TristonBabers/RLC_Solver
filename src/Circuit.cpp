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

}