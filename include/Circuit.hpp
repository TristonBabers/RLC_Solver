#ifndef Circuit_hpp
#define Circuit_hpp

#include "Node.hpp"

namespace RLC_SOLVER {

    class Circuit {
    public:
        Circuit(const std::vector<NodePtr>& aNodeList, const NodePtr& aStartNode, const NodePtr& anEndNode) :
                nodeList{aNodeList}, startNode{aStartNode}, endNode{anEndNode} {}
        std::vector<NodePtr> nodeList;
        NodePtr startNode;
        NodePtr endNode;
    };

}

#endif /* Circuit_hpp */