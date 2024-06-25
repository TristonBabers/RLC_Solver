#ifndef Component_hpp
#define Component_hpp

#include "Delimiter.hpp"
#include <string>
#include <optional>
#include <memory>

namespace RLC_SOLVER {

    class Node; // Forward Declare

    using NodePtr = std::shared_ptr<Node>;

    class Component {
    public:
        Component(const std::string& aName, const NodePtr& aNode) : name(aName), nextNode(aNode) {}

        std::string getName() inline const {
            return name;
        }

        std::string getImpedence() inline const {
            return delimiter(name);
        }

        std::string getCurrent() inline const {
            return delimiter(name);
        }

        std::string name;
        std::string current;
        NodePtr nextNode;
    };

    using ComponentPtr = std::shared_ptr<Component>;
}

#endif /* Component_hpp */