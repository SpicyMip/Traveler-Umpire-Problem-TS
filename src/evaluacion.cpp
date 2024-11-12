#include "evaluacion.h"

using namespace std;

int evaluarSolucion(const vector<int>& solucion, const InstanciaTUP& instancia) {
    int distanciaTotal = 0;
    int numRondas = instancia.matrizRondas.size();
    int numArbitros = instancia.numArbitros;

    for (int arbitro = 0; arbitro < numArbitros; ++arbitro) {
        for (int ronda = 1; ronda < numRondas; ++ronda) {
            int sedeActual = solucion[arbitro * numRondas + ronda - 1];
            int sedeSiguiente = solucion[arbitro * numRondas + ronda];
            distanciaTotal += instancia.matrizDistancias[sedeActual][sedeSiguiente];
        }
    }

    return distanciaTotal;
}
