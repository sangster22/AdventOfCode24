#include <iostream>
#include <fstream>
#include <vector>
#include <cmath> 
#include <sstream> 

using namespace std;

// Función para realizar Merge Sort (divide y vencerás)
void mergeSort(vector<int>& arr) {
    if (arr.size() <= 1) {
        return;
    }

    // Dividir el arreglo en dos mitades
    int mid = arr.size() / 2;
    vector<int> left(arr.begin(), arr.begin() + mid);
    vector<int> right(arr.begin() + mid, arr.end());

    // Recursivamente ordenar las dos mitades
    mergeSort(left);
    mergeSort(right);

    // Combinar las dos mitades ordenadas
    int i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] < right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    // Copiar cualquier elemento restante de left
    while (i < left.size()) {
        arr[k++] = left[i++];
    }

    // Copiar cualquier elemento restante de right
    while (j < right.size()) {
        arr[k++] = right[j++];
    }
}

// Función para calcular la distancia total entre dos listas
int calculateTotalDistance(const vector<int>& left, const vector<int>& right) {
    int total_distance = 0;

    // Calcular la distancia entre los elementos correspondientes
    for (size_t i = 0; i < left.size(); ++i) {
        total_distance += abs(left[i] - right[i]);
    }

    return total_distance;
}

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

    // Ordenar ambas listas usando Merge Sort (divide y vencerás)
    mergeSort(left);
    mergeSort(right);

    // Calcular la distancia total entre las listas ordenadas
    int total_distance = calculateTotalDistance(left, right);

    // Mostrar el resultado
    cout << "La distancia total es: " << total_distance << endl;

    return 0;
}
