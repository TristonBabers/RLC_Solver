#ifndef CircuitSolver_hpp
#define CircuitSolver_hpp

#include "Node.hpp"
#include "Circuit.hpp"

namespace RLC_SOLVER {

    class CircuitSolver {
    public:
        static Circuit solve(const std::vector<Circuit>& aCircuits);
    protected:
        static std::string findImpedences(const NodePtr& aNode, const NodePtr& anEndNode);
        static void findVoltages(const NodePtr& aStartNode, const NodePtr& anEndNode, const std::vector<NodePtr>& aNodeList);
        static void findCurrents(const std::vector<NodePtr>& aNodeList);
    };

}

#endif /* CircuitSolver_hpp */