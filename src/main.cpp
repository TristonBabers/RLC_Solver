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
#include "CircuitSolver.hpp"
#include "../dependencies/json.hpp"
#include "DAGifier.hpp"

namespace RLC_SOLVER {

    std::vector<Circuit> parseJSON(const std::string& aJSON) {
        return Circuit::fromJSON(aJSON);
    }

    std::string solve(const char* aJSON) {
        std::vector<Circuit> theCircuits{parseJSON(aJSON)};
        for (Circuit& theCircuit : theCircuits) {
            Dagifier::dagify(theCircuit);
        }
        Circuit theSolutionCircuit{CircuitSolver::solve(theCircuits)};
        return theSolutionCircuit.toJSON();
    }

}

int main(int argc, char* argv[]) {
    if (argc > 2) {
        // Testing goes here
        //RLC_SOLVER::test();
    } else if (argc == 2) {
        // DEBUG
        //std::cout << "Recieved:\n" << std::string(argv[1]) << "\n\n"; // DEBUG

        // Full Release
        std::cout << RLC_SOLVER::solve(argv[1]);

        // Pretty Mode
        //std::cout << nlohmann::json::parse(RLC_SOLVER::solve(argv[1])).dump(4);
    }
    return 0;
}