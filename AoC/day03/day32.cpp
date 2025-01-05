#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

using namespace std;

int main() {
    // Leer archivo de entrada
    ifstream inputFile("datos.txt");
    if (!inputFile) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    string line;
    string program;

    // Leer todo el contenido del archivo, preservando saltos de línea
    while (getline(inputFile, line)) {
        program += line + "\n";
    }

    inputFile.close();

    // Estado de las instrucciones (habilitado o deshabilitado)
    bool mulEnabled = true; // Las mul() están habilitadas inicialmente
    int sum = 0;

    // Expresiones regulares para instrucciones
    regex mulPattern(R"(mul\((\d+),(\d+)\))");
    regex doPattern(R"(^\s*do\(\))");
    regex dontPattern(R"(^\s*don't\(\))");

    // Analizar el programa línea por línea
    istringstream programStream(program);
    while (getline(programStream, line)) {
        smatch match;

        if (regex_search(line, match, doPattern)) {
            mulEnabled = true; // Habilitar futuras mul() instrucciones
        } else if (regex_search(line, match, dontPattern)) {
            mulEnabled = false; // Deshabilitar futuras mul() instrucciones
        } else if (regex_search(line, match, mulPattern)) {
            // Encontramos una instrucción mul(x, y)
            try {
                int x = stoi(match[1].str());
                int y = stoi(match[2].str());

                if (mulEnabled) {
                    // Si mul() está habilitada, realizamos la multiplicación
                    sum += x * y;
                }
            } catch (const invalid_argument &e) {
                cerr << "Error: Argumentos inválidos en mul(). Línea ignorada." << endl;
            } catch (const out_of_range &e) {
                cerr << "Error: Argumentos fuera de rango en mul(). Línea ignorada." << endl;
            }
        }
    }

    // Mostrar el resultado
    cout << "La suma de los resultados de las multiplicaciones habilitadas es: " << sum << endl;

    return 0;
}
