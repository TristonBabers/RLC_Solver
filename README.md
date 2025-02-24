# RLC Solver

A web-based tool for solving RLC circuits, implemented in C++. Calculate theoretical voltages and currents across resistors, capacitors, and inductors with ease.  

🔗 **Live Demo:** [TristonBabers.com/rlc-solver](https://tristonbabers.com/rlc-solver/)

---

## 📖 Overview

This repository contains the backend code for the RLC Solver, designed to compute voltages and currents for circuits composed of resistors, inductors, and capacitors. The solver handles various circuit configurations and dynamically recalculates node voltages and component currents based on input frequency changes.

---

## 🚩 Features
- Symbolic computation for real-time front-end recalculations.
- JSON data exchange using **nlohmann JSON** library.
- Server-client communication using PHP.

---

## 🛠️ Setup Instructions

1. **Requirements**  
   - C++20 or higher  
   - CMake (for building the project)  
   - [nlohmann JSON](https://github.com/nlohmann/json) library (Already included)

2. **Compilation**  
   ```bash
   mkdir build && cd build
   cmake ..
   make

3. **Running**
```
./rlc_solver [JSON Circuit Description]
./rlc_solver test all
./rlc_solver test [Test Name]
```

---

## 📝 Known Issues
- Parallel circuits: There is a known issue with solving certain parallel configurations accurately. A fix is in progress.

---

## 📋 To-Do List
- [X] Create Web App in Javascript for Circuit Building
- [x] Add PHP file for CGI data transfer
- [x] Backend C++ Core algorithm implementation
- [X] Integrate front-end symbolic computation for real-time updates
- [ ] Fix parallel circuit calculations (C++ update needed)
- [ ] Pretty up Frontend Interface
- [ ] Do More Testing

---

## 🚀 Usage
You can pass a JSON string directly to the program to solve a circuit:

Command:

```
./rlc_solver '{"Circuit":{"Nodes":{"node_20":[{"Resistor_5":"node_21"}],"node_21":[{"Resistor_5":"node_20"}]},"Sources":[{"Voltage_Source_0":{"VDD":"node_20","GND":"node_21"}}]}}'
```

Expected Output:
```
{
    "Circuit_Solution": [
        "{\"Circuit\":{\"Nodes\":{\"node_21\":\"0\",\"node_20\":\"{Voltage_Source_0}\"},\"Components\":{}}}"
    ]
}
```
Using this output, you can calculate voltages and currents by solving the equations provided in the solution. The Components array is currently unused but reserved for future functionality.

---

## 📄 License
© Triston Babers 2025. All Rights Reserved.