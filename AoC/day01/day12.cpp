#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map> // Para contar las ocurrencias
#include <sstream>

using namespace std;

int main() {
    // Abrir el archivo de entrada
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Error al abrir el archivo de entrada." << endl;
        return 1;
    }

    vector<int> left, right;
    int left_num, right_num;

    // Leer los datos del archivo
    while (inputFile >> left_num >> right_num) {
        left.push_back(left_num);
        right.push_back(right_num);
    }

    inputFile.close(); // Cerrar el archivo

    // Usar unordered_map para contar las ocurrencias de cada número en la lista derecha
    unordered_map<int, int> rightCount;

    // Contar las ocurrencias de cada número en la lista derecha
    for (int num : right) {
        rightCount[num]++;
    }

    // Calcular el puntaje de similitud
    int similarityScore = 0;

    // Para cada número en la lista izquierda, multiplicamos por las ocurrencias en la lista derecha
    for (int num : left) {
        similarityScore += num * rightCount[num]; // Si el número no está en rightCount, el valor será 0
    }

    // Mostrar el resultado
    cout << "El puntaje de similitud es: " << similarityScore << endl;

    return 0;
}
