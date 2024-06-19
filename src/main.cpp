/* Algorithm Description:
* 1. Create a graph of "routes" from t
* 
* 
* 
* Limitations:
* - Only works if there is a single voltage source
*/

#include <complex>

using Complex = std::complex<float>;

// Circuit = component
class Circuit : public Component {
    Circuit (float aVoltage, float aCurrent=null) : v(aVoltage), c(aCurrent) {};
};

class Node {
    std::string theName;
    std::vector<Component> connections;
};

class Resistor : public Component<Resistor> {
protected:
    doImpedence() {
        return Complex{Resistance};
    };
    float Resistance;
};

template <typename Derived>
class Component {
public:
    std::shared_pointer<Node> crossFrom(const std::shared_pointer<Node> aNode) {
        if (aNode == node1) return node2;
        return node1;
    }
    Complex getImpedence() {
        return Derived->doImpedence();
    }
    std::shared_pointer<Node> node1;
    std::shared_pointer<Node> node2;
    std::optional<Voltage> v;
    std::optional<Current> c;
};

class Route {
    std::variant<std::vector<Route>, std::vector<Component>> route;
};

std::vector<Route> buildRoutes(Component aComponent, Component) {
    std::vector<Route> theRoutes;
    for (theConnection : aComponent.node1.connections) {
        std::shared_pointer<Node> theNextNode{theConnection.crossFrom(aComponent.node1)};
        if (theNextNode != aComponent.node2) {
            theRoutes.push_back(buildRoute(theNextNode));
        } else {
            theRoutes.push_back(Route{theConnection});
        }
    }
    return theRoutes;
}

findImpedences(std::vector<Route> aRoutes) {
    while (aRoutes) {
        Route aRoutes
        
    }
}

void solve(theCircuit) {
    std::vector<Route> theRoutes{buildRoutes(theCircuit)};
    findImpedences(theRoutes);
    findVoltagesAndCurrents(theRoutes);
}