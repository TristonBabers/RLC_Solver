#ifndef Component_hpp
#define Component_hpp

#include <memory>
#include <complex>

namespace RLC_SOLVER {

    class Node; // Forward Declare

    using NodePtr = std::shared_ptr<Node>;
    using Complex = std::complex<float>;

    class Component {
    public:
        Component(const NodePtr& aNode) : nextNode(aNode) {}

        virtual Complex getImpedence() const {
            return 9999; // Debug Error Value
        }

        virtual ~Component() = default;

        float current;
        NodePtr nextNode;
    };

    class Resistor : public Component {
    public:
        Resistor(const NodePtr& aNode, float aResistance) : Component(aNode), resistance(aResistance) {}

        virtual Complex getImpedence() const override {
            return Complex{resistance};
        }

    protected:
        float resistance;
    };

    class Inductor : public Component {
    public:
        Inductor(const NodePtr& aNode, float anInductance, float aFrequency) : Component(aNode), inductance(anInductance) {}

        virtual Complex getImpedence() const override {
            return Complex{inductance};
        }

    protected:
        float inductance;
    };

}

#endif /* Component_hpp */