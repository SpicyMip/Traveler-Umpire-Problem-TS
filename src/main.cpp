#include <iostream>
#include <filesystem>
#include "instancia.h"
#include "solucion_inicial.h"
#include "evaluacion.h"
#include "output_writer.h"

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
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " <archivo_instancia> [semilla]" << endl;
        return 1;
    }

    string rutaArchivo = argv[1];
    string nombreInstancia = fs::path(rutaArchivo).stem();
    InstanciaTUP instancia = leerInstancia(rutaArchivo);

    unsigned int semilla;
    if (argc >= 3) {
        semilla = atoi(argv[2]);
    } else {
        semilla = time(nullptr); 
    }
    srand(semilla);

    int N = instancia.numArbitros;
    int R = 4 * N - 2;

    int d1 = rand() % (N + 1);           
    int d2 = rand() % ((N / 2) + 1);     


    vector<int> solucionInicial = generarSolucionInicial(instancia, N, d1, d2, semilla);

    int distanciaTotal = evaluarSolucion(solucionInicial, instancia);

    cout << "Semilla: " << semilla << endl;
    cout << "Distancia: " << distanciaTotal << endl;
    cout << "d1: " << d1 << " ; d2: " << d2 << endl;
    imprimirMatrizAsignaciones(solucionInicial, N, R);


    guardarOutput(nombreInstancia, semilla, distanciaTotal, d1, d2, solucionInicial, N, R);

    return 0;
}
