#include "instancia.h"
#include <fstream>
#include <iostream>

using namespace std;

InstanciaTUP leerInstancia(const string& archivo) {
    InstanciaTUP instancia;
    ifstream archivoInstancia(archivo);

    if (!archivoInstancia.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << archivo << endl;
        exit(1);
    }

    // Lee el número de árbitros
    archivoInstancia >> instancia.numArbitros;
    if (instancia.numArbitros <= 0) {
        cerr << "Error: El número de árbitros debe ser mayor que cero." << endl;
        exit(1);
    }

    // Lee la matriz de distancias y calcular el número de equipos
    vector<vector<int>> matrizDistancias;
    int valor;
    while (archivoInstancia >> valor) {
        vector<int> fila;
        fila.push_back(valor);

        for (int j = 1; archivoInstancia >> valor; ++j) {
            fila.push_back(valor);
            if (archivoInstancia.peek() == '\n' || archivoInstancia.peek() == EOF) {
                break;
            }
        }

        matrizDistancias.push_back(fila);

        if (matrizDistancias.size() == fila.size()) {
            break;
        }
    }

    int numEquipos = matrizDistancias.size();
    instancia.matrizDistancias = matrizDistancias;

    // Lee la matriz de rondas (r x n)
    vector<vector<int>> matrizRondas;
    while (archivoInstancia >> valor) {
        vector<int> filaRonda;
        filaRonda.push_back(valor);

        for (int j = 1; j < numEquipos; ++j) {
            archivoInstancia >> valor;
            filaRonda.push_back(valor);
        }

        matrizRondas.push_back(filaRonda);
    }

    instancia.matrizRondas = matrizRondas;

    archivoInstancia.close();
    cout << "Instancia leída correctamente." << endl;
    return instancia;
}
