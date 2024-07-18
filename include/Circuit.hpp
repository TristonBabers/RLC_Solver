#ifndef Circuit_hpp
#define Circuit_hpp

#include "Node.hpp"

namespace RLC_SOLVER {

    class Circuit {
    public:
        Circuit(const std::vector<NodePtr>& aNodeList, const NodePtr& aStartNode, const NodePtr& anEndNode, const std::vector<ComponentPtr>& componentList={});
        std::string toJSON();
        static std::vector<Circuit> fromJSON(const std::string& aJsonData);

        std::vector<NodePtr> nodeList;
        std::vector<ComponentPtr> componentList; // Currently unused except for display purposes
        NodePtr startNode;
        NodePtr endNode;
    };

}

#endif /* Circuit_hpp */