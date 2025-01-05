#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Función que verifica si un informe es seguro (no estrictamente decreciente)
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


// Función que verifica si un informe puede ser seguro eliminando un solo nivel
bool puedeSerSeguroConEliminacion(const vector<int>& informe) {
    for (size_t i = 0; i < informe.size(); ++i) {
        vector<int> nuevoInforme = informe;
        nuevoInforme.erase(nuevoInforme.begin() + i);

        if (esSeguro(nuevoInforme)) {
            return true; // Si se vuelve seguro, retornamos true
        }
    }
    return false; // Si no se puede hacer seguro eliminando un nivel
}

// Función para contar cuántos informes son seguros
int contarInformesSeguros(const vector<vector<int>>& informes) {
    int seguros = 0;
    for (const auto& informe : informes) {
        // Si el informe es seguro directamente o puede ser seguro eliminando un nivel
        if (esSeguro(informe) || puedeSerSeguroConEliminacion(informe)) {
            ++seguros;
        }
    }
    return seguros;
}

// Función que lee los informes desde un archivo
vector<vector<int>> leerInformesDesdeFichero(const string& nombreFichero) {
    vector<vector<int>> informes;
    ifstream archivo(nombreFichero);

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo!" << endl;
        return informes; 
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        vector<int> informe;
        int numero;
        while (ss >> numero) {
            informe.push_back(numero);
        }
        informes.push_back(informe);
    }

    archivo.close();
    return informes;
}

int main() {

    string nombreFichero = "datos.txt"; 

    
    vector<vector<int>> informes = leerInformesDesdeFichero(nombreFichero);
    int seguros = contarInformesSeguros(informes);
    cout << "Número de informes seguros: " << seguros << endl;

    return 0;
}
