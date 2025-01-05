#include <iostream>
#include <fstream>
#include <regex>
#include <string>

using namespace std;

int procesar_memoria(const string& memoria) {
    // Expresión regular para encontrar las instrucciones mul(X, Y) con números de 1 a 3 dígitos
    regex patron(R"(mul\((\d{1,3}),(\d{1,3})\))");
    smatch coincidencia;
    int suma_total = 0;
    
    string::const_iterator inicio = memoria.cbegin();
    string::const_iterator fin = memoria.cend();
    
    // Buscar todas las coincidencias en la memoria
    while (regex_search(inicio, fin, coincidencia, patron)) {
        // Extraemos los números X y 7Y
        int x = stoi(coincidencia[1].str());
        int y = stoi(coincidencia[2].str());
        
        // Realizamos la multiplicación y sumamos al total
        suma_total += x * y;
        
        // Avanzamos el iterador para seguir buscando más coincidencias
        inicio = coincidencia[0].second;
    }

    return suma_total;
}

int main() {
    // Nombre del archivo que contiene la memoria dañada
    string nombre_archivo = "datos.txt";
    
    // Abrimos el archivo
    ifstream archivo(nombre_archivo);
    
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo!" << endl;
        return 1;
    }

    // Leemos todo el contenido del archivo
    string memoria_danada((istreambuf_iterator<char>(archivo)), istreambuf_iterator<char>());
    
    // Llamamos a la función para procesar la memoria
    int resultado = procesar_memoria(memoria_danada);
    
    // Imprimimos el resultado
    cout << "El resultado de las multiplicaciones es: " << resultado << endl;

    // Cerramos el archivo
    archivo.close();
    
    return 0;
}
