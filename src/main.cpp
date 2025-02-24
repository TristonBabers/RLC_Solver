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
#include <string>
#include <functional>
#include <algorithm>
#include "../dependencies/json.hpp"
#include "CircuitSolver.hpp"
#include "DAGifier.hpp"
#include "Tester.cpp"


namespace RLC_SOLVER {

    std::string solve(const char* aJSON) {
        std::vector<Circuit> theCircuits{Circuit::fromJSON(aJSON)};
        for (Circuit& theCircuit : theCircuits) {
            Dagifier::dagify(theCircuit);
        }
        Circuit theSolutionCircuit{CircuitSolver::solve(theCircuits)};
        return theSolutionCircuit.toJSON();
    }

}

int main(int argc, char* argv[]) {
    if (argc == 3) {
        RLC_SOLVER::Tester theTester;
        static std::map<std::string, std::function<bool(std::stringstream&)>> theTests{
            {"simple", [&](std::stringstream &anOut){
                return theTester.simpleCircuit(anOut);}},
            {"voltage_divider", [&](std::stringstream &anOut){
                return theTester.voltageDivider(anOut);}},
            {"advanced", [&](std::stringstream &anOut){
                return theTester.advancedCircuit(anOut);}}
            };

        std::string theTestToRun{argv[2]};
        std::transform(theTestToRun.begin(), theTestToRun.end(), theTestToRun.begin(),
                [](unsigned char c){ return std::tolower(c);});

        if (theTestToRun == "all") {
            for (auto& [theTestName, theTest] : theTests) {
                std::stringstream theOutput;
                bool theResult = theTest(theOutput);
                const char* theStatus[]={"FAIL","PASS"};
                std::cout << theTestName << " test " << theStatus[theResult] << "\n";
                std::cout << (theResult ? "---------------------------------\n" : "VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV\n" + theOutput.str() + "\n---------------------------------\n");
            }
        } else if(theTests.count(theTestToRun)) {
            std::stringstream theOutput;
            bool theResult = theTests[theTestToRun](theOutput);
            const char* theStatus[]={"FAIL","PASS"};
            std::cout << theTestToRun << " test " << theStatus[theResult] << "\n";
            std::cout << (theResult ? "---------------------------------\n" : "---------------------------------\n" + theOutput.str() + "\n---------------------------------\n");
        } else {
            std::cout << "Unknown Test\n";
        }
    } else if (argc == 2) {
        // Full Release
        //std::cout << RLC_SOLVER::solve(argv[1]);

        // Pretty Mode
        std::cout << argv[1];
        std::cout << nlohmann::json::parse(RLC_SOLVER::solve(argv[1])).dump(4);
    }
    return 0;
}