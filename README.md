# DFA Minimization Project

## Members
- Samuel Herrera Galvis
- Emmanuel Alvarez Castrillon

## Student’s Class Number
SI2002-2 (7309)

## Development Environment
- **Operating System:** Windows 10 x64bits
- **Programming Language:** C++
- **IDE:** Visual Studio Code

## Running Instructions

When you run the code, a menu will appear:
1. To enter the exercise through the console, press `1` then press `Enter`.
2. To enter the exercise through a text file, press `2` then press `Enter`.
3. To exit the program, press `3` then press `Enter`.

### Console Input
If you chose to enter the exercise through the console, follow these steps:
1. Enter the number of DFAs you want to input.
2. Enter the number of states of the DFA.
3. Enter its alphabet, with each character separated by a space.
4. Enter its final states, with each state separated by a space.
5. Enter the transition table. For each state, enter the states to which it transitions, separated by a space.
6. The program will display the pairs of states that are equivalent in lexicographical order of the automaton.
7. Repeat this process until you finish entering all DFAs.

### File Input
If you chose to enter the exercise through a file, ensure the file is in the same folder as the main program. Enter the file name with its extension (e.g., `DFA.txt`). The result of the exercise will be displayed.

## Explanation of the Algorithm

### Minimization Algorithm (minimizeDFA)

The algorithm identifies equivalent states by distinguishing pairs:

**Step 1: Initialization of the Distinguishability Matrix**
- A table `distinguishable[i][j]` is created (boolean matrix of size numStates × numStates).
- Pairs (i, j) where one is final and the other is not are marked as distinct.

**Step 2: Distinction Propagation**
- For each pair (i, j), if a transition from i and j leads to already distinguished states, then i and j must also be distinguished.

**Step 3: Construction of the Set of Equivalent States**
- Pairs (i, j) that were not marked as distinguishable, i.e., those that are equivalent, are stored for later display.

The rest of the code captures the data, such as the tuple for each DFA, and creates a nice output.
