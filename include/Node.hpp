#ifndef Node_hpp
#define Node_hpp

#include <memory>
#include <optional>
#include <vector>
#include "Component.hpp"

namespace RLC_SOLVER {

    class Node {
    public:
        Node(const std::string& aName, std::vector<std::unique_ptr<Component>> aConnections={}) :
                name(aName), connections{std::move(aConnections)}, impedence{std::nullopt}, voltage{0} {}

        Node(const std::string& aName, float aVoltage, std::vector<std::unique_ptr<Component>> aConnections={}) :
                name(aName), connections{std::move(aConnections)}, impedence{std::nullopt}, voltage{aVoltage} {}

        bool operator==(const Node& anotherNode) const {
            return name == anotherNode.name;
        }

        std::string name;
        float voltage;
        std::optional<Complex> impedence;
        std::vector<std::unique_ptr<Component>> connections;
    };

}

#endif /* Node_hpp */