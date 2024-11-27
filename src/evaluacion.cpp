#include "evaluacion.h"
#include "utils.h" 

using namespace std;

int evaluarSolucion(const vector<int>& solucion, const InstanciaTUP& instancia) {
    int distanciaTotal = 0;
    int numRondas = instancia.matrizRondas.size();
    int numArbitros = instancia.numArbitros;

    for (int arbitro = 0; arbitro < numArbitros; ++arbitro) {
        int idx = arbitro * numRondas;
        int gameAnterior = solucion[idx];
        int rondaAnterior = 0;

        // Obtener la sede anterior
        int equipoLocalAnterior, equipoVisitanteAnterior;
        obtenerEquiposDelJuego(instancia, rondaAnterior, gameAnterior, equipoLocalAnterior, equipoVisitanteAnterior);
        int sedeAnterior = equipoLocalAnterior;

        for (int ronda = 1; ronda < numRondas; ++ronda) {
            int idxActual = arbitro * numRondas + ronda;
            int gameActual = solucion[idxActual];

            // Obtener la sede actual
            int equipoLocalActual, equipoVisitanteActual;
            obtenerEquiposDelJuego(instancia, ronda, gameActual, equipoLocalActual, equipoVisitanteActual);
            int sedeActual = equipoLocalActual;

            // Sumar la distancia entre las sedes
            distanciaTotal += instancia.matrizDistancias[sedeAnterior][sedeActual];

            // Actualizar sede anterior
            sedeAnterior = sedeActual;
        }
    }

    return distanciaTotal;
}
