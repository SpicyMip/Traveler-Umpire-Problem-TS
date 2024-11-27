#include <iostream>
#include <filesystem>
#include "instancia.h"
#include "solucion_inicial.h"
#include "evaluacion.h"
#include "output_writer.h"
#include "tabu_search.h"

namespace fs = std::filesystem;

using namespace std;

void imprimirMatrizAsignaciones(const vector<int>& solucionInicial, int numArbitros, int numRondas) {
    cout << "" << endl;
    for (int arbitro = 0; arbitro < numArbitros; ++arbitro) {
        cout << "Árbitro " << arbitro + 1 << ": ";
        for (int ronda = 0; ronda < numRondas; ++ronda) {
            cout << solucionInicial[arbitro * numRondas + ronda] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Uso: " << argv[0] << " <archivo_instancia> <d1> <d2> <semilla>" << endl;
        return 1;
    }

    string rutaArchivo = argv[1];
    string nombreInstancia = fs::path(rutaArchivo).stem();
    InstanciaTUP instancia = leerInstancia(rutaArchivo);

    unsigned int semilla;
    if (argc >= 5) {
        semilla = atoi(argv[4]);
    } else {
        semilla = time(nullptr); 
    }
    srand(semilla);

    int N = instancia.numArbitros;
    int R = 4 * N - 2;

    int d1 = atoi(argv[2]);
    int d2 = atoi(argv[3]);

    if (d1 < 0 || d1 > N) {
        cerr << "Error: d1 debe estar entre 0 y N (N = " << N << ")" << endl;
        return 1;
    }
    if (d2 < 0 || d2 > (N / 2)) {
        cerr << "Error: d2 debe estar entre 0 y N/2 (N/2 = " << N / 2 << ")" << endl;
        return 1;
    }

    vector<int> solucionInicial = generarSolucionInicial(instancia, N, d1, d2, semilla);

    int maxIterations = 1000; 
    int tenureMin = 5;
    int tenureMax = 15;

    vector<int> mejorSolucion = tabuSearch(solucionInicial, instancia, N, R, maxIterations, tenureMin, tenureMax, d1, d2);

    int distanciaTotal = evaluarSolucion(mejorSolucion, instancia);

    cout << "Semilla: " << semilla << endl;
    cout << "Distancia: " << distanciaTotal << endl;
    cout << "d1: " << d1 << " ; d2: " << d2 << endl;
    imprimirMatrizAsignaciones(solucionInicial, N, R);


    guardarOutput(nombreInstancia, semilla, distanciaTotal, d1, d2, mejorSolucion, N, R);

    return 0;
}
