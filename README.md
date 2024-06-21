# RLC_Solver
Solves RLC circuits via a website interface, implemented in C++. For more information, see [TristonBabers.com/rlc-solver](TristonBabers.com/rlc-solver).

## Overview
This repository contains the backend code for my website's RLC_Solver. It is designed to solve circuits consisting of only resistors, capacitors, and inductors calculating the theoretical voltages and currents across each component.

## To Do List:
- Now that the algorithm is working soundly, I want to ensure that front-end computation is possible. This means that when I change the frequency of the circuit, the node voltages and component currents are recalculated on the front-end; so every calculation must be performed symbolically.

### Requirements
- Need to find or build an appropriate Symbolic library for C++.
  - Preferably one that plays well with Javascript as that is where the calculations will be evaluated ultimately.
- **[ALTERNATIVELY]** Can store all of the expressions as strings, and evaluate them using Javascript libraries. This would simplify the dependencies alot.

- Need to make sure Javascript has DTFT libraries, but it probably does.

### Important Takeaways
- No voltage or impedence information needs to actually be sent to the backend, just the circuit layout.
- **???** Why is this project even being done in C++? Would it be faster to solve and compute everything in Javascript?

## Setup Information
-Will be updated eventually.
