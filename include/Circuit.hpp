#ifndef Circuit_hpp
#define Circuit_hpp

#include "Node.hpp"

namespace RLC_SOLVER {

    class Circuit {
    public:
        Circuit(const std::vector<NodePtr>& aNodeList, const NodePtr& aStartNode, const NodePtr& anEndNode, const std::vector<ComponentPtr>& componentList={});
        std::string toJSON();

        std::vector<NodePtr> nodeList;
        std::vector<ComponentPtr> componentList;
        NodePtr startNode;
        NodePtr endNode;
    };

}

#endif /* Circuit_hpp */