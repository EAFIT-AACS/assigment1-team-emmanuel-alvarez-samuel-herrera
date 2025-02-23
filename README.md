Members: Samuel Herrera Galvis and Emmanuel Alvarez Castrillon 
Student’s class number: SI2002-2 (7309)
Operating system: Windows 10 x64bits, programming language: c++, IDE: Visual Studio Code

running instructions:

When you run the code, a menu will appear, to enter the exercise through the console press 1 then press enter, 
to enter the exercise through a txt file press 2 then press enter, to exit the program press 3 then press enter.

If you chose to enter the exercise through the console you will have to follow the instructions that the program tells you, 
you have to enter the number of DFA's you want to enter, then you will enter the number of states of the DFA, then you will 
enter its alphabet each character separated by a space, then you will enter its final states each state separated by a space, 
then you will have to make the transition table what you should do is in the state that it indicates, enter the states to 
which the state goes (you must leave a space between each state), then you will see the pairs of states that are equivalent 
in lexicographical order of the automaton, repeat this process until you finish the last DFA.

If you chose to enter the exercise through a file, you must have the file in the same folder as the main one and you must enter the name of the file with its extension, 
for example DFA.txt, and then the result of the exercise will appear.

Explanation of the algorithm:

Minimization Algorithm (minimizeDFA())
The algorithm identifies equivalent states by distinguishing pairs:

Step 1: Initialization of the distinguishability matrix.
A table distinguishable[i][j] is created (boolean matrix of size numStates × numStates).
Pairs (i, j) where one is final and the other is not are marked as distinct.

Step 2: Distinction propagation.
For each pair (i, j), if a transition from i and j leads to already distinguished states, then i and j must also be distinguished.

Step 3: Construction of the set of equivalent states.
Pairs (i, j) that were not marked as distinguishable, i.e. those that are equivalent, are stored for later display.

The rest of the code was made to capture the data, such as the tuple for each DFA, and was also made to create a nice output.
