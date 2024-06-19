/* Algorithm Description:
* 1. Create a graph of "routes" from the node around a voltage source to
* 
* 
* 
* Limitations:
* - Only works if there is a single voltage source
* --> Just use superposition on all other sources, and we're fine.
*/

#include <iostream>
#include <unordered_map>
#include <complex>
#include <optional>
#include <memory>

namespace RLC_SOLVER {

    using Complex = std::complex<float>;

    struct Node {
        std::string name;
        std::optional<float> voltage;
        std::optional<float> current;
    };

   // template <typename Derived>
    class Component {
    public:
        /*
        std::shared_ptr<Node> crossFrom(const std::shared_ptr<Node> aNode) {
            if (aNode == node1) return node2;
            return node1;
        }*/
        virtual Complex getImpedence() {
            return 0;
        }
        std::string node1;
        std::string node2;
    };

    using CircuitMap = std::unordered_map<std::string, std::vector<Component>>;
    using Path = std::vector<Component>;
    
    struct Circuit {
        std::string start;
        std::string end;
        CircuitMap map;
    };

    //class Resistor : public Component<Resistor> {
    class Resistor : public Component {
    public:
        virtual Complex getImpedence() override {
            return Complex{Resistance};
        };
    protected:
        float Resistance;
    };

    void findAllPaths(const CircuitMap& aCircuit, const std::string& aStart,
                                   const std::string& anEnd, std::vector<std::string>& aPath,
                                   std::vector<Component>& anEdgePath,
                                   std::vector<std::vector<Component>>& aVectorOfPaths) {
        aPath.push_back(aStart);
        if (aStart == anEnd) {
            aVectorOfPaths.push_back(anEdgePath);
            auto theItr = aCircuit.find(aStart);
            if (theItr != aCircuit.end()) {
                for (const auto& theComponent : theItr->second) {
                    const std::string& theNode = theComponent.node2;
                    if (find(aPath.begin(), aPath.end(), theNode) == aPath.end()) {
                        anEdgePath.push_back(theComponent);
                        findAllPaths(aCircuit, theNode, anEnd, aPath, anEdgePath, aVectorOfPaths);
                        anEdgePath.pop_back();
                    }
                }
            }
        }
    }

    void findImpedences(std::vector<Path>& aVectorOfPaths) {
        //while (aVectorOfPaths) {
        //}
    }

    void findVoltagesAndCurrents(std::vector<Path>& aVectorOfPaths) {
    
    }

    void solve(const Circuit& aCircuit) {
        std::vector<std::string> thePath;
        std::vector<Component> theEdgePath;
        std::vector<Path> thePaths;
        findAllPaths(aCircuit.map, aCircuit.start, aCircuit.end, thePath, theEdgePath, thePaths);
        findImpedences(thePaths);
        findVoltagesAndCurrents(thePaths);
    }
}

    int main() {
        //std::cout << "test\n";
        return 0;
    }