#ifndef Node_hpp
#define Node_hpp

#include <memory>
#include <optional>
#include <vector>
#include "Delimiter.hpp"
#include "Component.hpp"

namespace RLC_SOLVER {

    class Node {
    public:
        Node(const std::string& aName, const std::optional<std::string>& anImpedence=std::nullopt, std::vector<std::shared_ptr<Component>> aConnections={}) :
                name(aName), voltage{0}, connections{std::move(aConnections)}, impedence{anImpedence} {}

        bool operator==(const Node& anotherNode) const {
            return name == anotherNode.name;
        }

        std::string getName() const {
            return name;
        }

        std::string getVoltage() const {
            return delimiter(name);
        }

        std::string getSource() const {
            return delimiter(voltage);
        }

        size_t preOrder{0};
        size_t postOrder{0};
        bool visited{false};
        std::string name;
        std::string voltage;
        std::optional<std::string> impedence;
        std::vector<std::shared_ptr<Component>> connections;
    };

}

#endif /* Node_hpp */