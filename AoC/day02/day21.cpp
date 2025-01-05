#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

// Función para verificar si un informe es seguro
bool esSeguro(const vector<int>& niveles) {
    bool creciente = true, decreciente = true;

    for (size_t i = 1; i < niveles.size(); i++) {
        int diff = niveles[i] - niveles[i - 1];

        // Verificar si la diferencia está entre [1, 3]
        if (abs(diff) < 1 || abs(diff) > 3) {
            return false;
        }

        // Determinar si los niveles no son consistentes en una dirección
        if (diff > 0) {
            decreciente = false;
        } else if (diff < 0) {
            creciente = false;
        }
    }

    // Es seguro si es completamente creciente o decreciente
    return creciente || decreciente;
}

int main() {
    ifstream archivo("datos.txt"); 
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo" << endl;
        return 1;
    }

    string linea;
    int informesSeguros = 0;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        vector<int> niveles;
        int nivel;

        // Leer los niveles de la línea actual
        while (ss >> nivel) {
            niveles.push_back(nivel);
        }

        // Verificar si el informe es seguro
        if (esSeguro(niveles)) {
            informesSeguros++;
        }
    }

    archivo.close();

    cout << "Cantidad de informes seguros: " << informesSeguros << endl;

    return 0;
}
