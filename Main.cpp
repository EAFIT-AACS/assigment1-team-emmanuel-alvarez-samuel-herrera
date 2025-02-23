#include <iostream> //Permite la entrada y salida de datos
#include <vector> //estructura de datos que se puede redimensionar dinámicamente
#include <set>
#include <map>
#include <algorithm>
#include <sstream> //Para separar datos de una cadena.(ss)
#include <limits> // Para ayudarme a controlar errores
#include <fstream> //Permite crear, leer y escribir archivos.

using namespace std;

// Estructura para representar un DFA
struct DFA {
    int numStates;
    vector<char> alphabet;
    set<int> finalStates;
    vector<vector<int>> transitionTable;
};

// Declaración de funciones
DFA readDFA();
set<pair<int, int>> minimizeDFA(DFA &dfa);
DFA readDFAFromFile(ifstream &file);


int main() {
    cout<<"Bienvenido a nuestro programa\nEste programa da solucion a la primera actividad propuesta del curso"<<endl;

    while(true){
        int eleccion;
        cout<<"-------------------------Menú-------------------------\n1.Ingresar el ejercicio por medio de consola\n2.Ingresar el ejercicio por medio de un archivo .txt\n3.Para salir del programa"<<endl;
        cin>>eleccion;
            if (cin.fail()) { //verificar si la operacion de entrada falla
                cin.clear(); // Limpiar el estado de error, para poder despues hacer mas entradas
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar todos los caracteres hasta el final de la línea
                cout << "Entrada inválida. Por favor, ingrese un número entero." << endl;
                continue; // Volver a pedir la entrada
            }

        if(eleccion==3){
          break;
        }
        switch (eleccion){
            case 1:
                {
                cout << "Ingrese el número de casos de prueba: ";
                int cases;
                cin >> cases;
                while (cases--) {
                    cout << "\n--- Nuevo caso de prueba ---\n";
                    cout << "Ingrese el número de estados del DFA: ";
                    DFA dfa = readDFA();
                    set<pair<int, int>> equivalentStates = minimizeDFA(dfa);
            
                    for (auto &pair : equivalentStates) {
                        cout << "(" << pair.first << ", " << pair.second << ") ";
                    }
                    cout << endl;
                }
                break;
            }
            case 2:
                {
                cout << "Ingrese el nombre del archivo incluyendo su extension ejemplo DFA.txt: ";
                string nombre_archivo;
                cin >> nombre_archivo;
                ifstream file(nombre_archivo);

                if (!file) {
                    cout << "Error al abrir el archivo, asegurese de que tiene la extension\nasegurese que el archivo esta en la misma carpeta que el Main" << endl;
                    break;
                }

                int cases;
                file >> cases;
                file.ignore();
                while (cases--) {
                    DFA dfa = readDFAFromFile(file);
                    set<pair<int, int>> equivalentStates = minimizeDFA(dfa);

                    for (auto &pair : equivalentStates) {
                        cout << "(" << pair.first << ", " << pair.second << ") ";
                    }
                    cout << endl;
                }
                file.close();

                break;
            }
        }
    }
    return 0;
}

// Función para leer un DFA desde la entrada estándar
DFA readDFA() {
    DFA dfa;
    cin >> dfa.numStates;
    cin.ignore();
    
    cout << "Ingrese el alfabeto (letras separadas por espacios): ";
    string line;
    getline(cin, line);

    for (char c : line) {
        if (c != ' ') dfa.alphabet.push_back(c);
    }

    cout << "Ingrese los estados finales (números separados por espacios): ";
    getline(cin, line);
    istringstream finalStream(line);
    int finalState;
    while (finalStream >> finalState) {
        dfa.finalStates.insert(finalState);
    }

    cout << "Ingrese la tabla de transiciones (" << dfa.numStates << " filas x " << dfa.alphabet.size() << " columnas):\n";
    cout << "Solo ingresar el estado a donde se dirige, ejemplo: si el alfabeto tiene 2 caracteres ingresar 1 4 no 0 1 4\n";
    dfa.transitionTable.resize(dfa.numStates, vector<int>(dfa.alphabet.size()));
    for (int i = 0; i < dfa.numStates; i++) {
        cout << "Estado " << i << ": ";
        for (int j = 0; j < dfa.alphabet.size(); j++) {
            cin >> dfa.transitionTable[i][j];
            

        }
    }

    return dfa;
}

// Función para minimizar un DFA y encontrar estados equivalentes
set<pair<int, int>> minimizeDFA(DFA &dfa) {
    vector<vector<bool>> distinguishable(dfa.numStates, vector<bool>(dfa.numStates, false));

    // Marcar pares de estados donde uno es final y el otro no
    for (int i = 0; i < dfa.numStates; i++) {
        for (int j = i + 1; j < dfa.numStates; j++) {
            if ((dfa.finalStates.count(i) && !dfa.finalStates.count(j)) ||
                (!dfa.finalStates.count(i) && dfa.finalStates.count(j))) {
                distinguishable[i][j] = true;
            }
        }
    }

    bool changed;
    do {
        changed = false;
        for (int i = 0; i < dfa.numStates; i++) {
            for (int j = i + 1; j < dfa.numStates; j++) {
                if (!distinguishable[i][j]) {
                    for (int k = 0; k < dfa.alphabet.size(); k++) {
                        int nextState1 = dfa.transitionTable[i][k];
                        int nextState2 = dfa.transitionTable[j][k];

                        if (nextState1 != nextState2 && distinguishable[min(nextState1, nextState2)][max(nextState1, nextState2)]) {
                            distinguishable[i][j] = true;
                            changed = true;
                            break;
                        }
                    }
                }
            }
        }
    } while (changed);

    set<pair<int, int>> equivalentStates;
    for (int i = 0; i < dfa.numStates; i++) {
        for (int j = i + 1; j < dfa.numStates; j++) {
            if (!distinguishable[i][j]) {
                equivalentStates.insert({i, j});
            }
        }
    }
    return equivalentStates;
}

// Función para leer un DFA desde un archivo
DFA readDFAFromFile(ifstream &file) {
    DFA dfa;
    string line;

    // Leer número de estados
    getline(file, line);
    dfa.numStates = stoi(line);

    // Leer alfabeto
    getline(file, line);
    for (char c : line) {
        if (c != ' ') dfa.alphabet.push_back(c);
    }

    // Leer estados finales
    getline(file, line);
    istringstream finalStream(line);
    int finalState;
    while (finalStream >> finalState) {
        dfa.finalStates.insert(finalState);
    }

    // Leer tabla de transiciones
    dfa.transitionTable.resize(dfa.numStates, vector<int>(dfa.alphabet.size()));
    for (int i = 0; i < dfa.numStates; i++) {
        getline(file, line);
        istringstream transitionStream(line);
        int stateIndex;
        transitionStream >> stateIndex; // Ignorar el estado al inicio de la línea
        for (int j = 0; j < dfa.alphabet.size(); j++) {
            transitionStream >> dfa.transitionTable[i][j];
        }
    }
    return dfa;
}
