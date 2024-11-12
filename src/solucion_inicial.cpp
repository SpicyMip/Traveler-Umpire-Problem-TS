#include "solucion_inicial.h"
#include <algorithm>
#include <random>
#include <set>

using namespace std;

vector<int> generarSolucionInicial(const InstanciaTUP& instancia, int N, int d1, int d2, unsigned int semilla) {
    int numRondas = 4 * N - 2;
    int numEquipos = 2 * N;
    vector<int> solucionInicial(N * numRondas, -1);

    mt19937 g(semilla);
    vector<int> equipos(numEquipos);
    iota(equipos.begin(), equipos.end(), 0);

    for (int arbitro = 0; arbitro < N; ++arbitro) {
        vector<int> rondas(numRondas, -1);
        int consecutivasSede = 0;
        int consecutivasEquipo = 0;
        int ultimoEquipo = -1;
        int ultimaSede = -1;

        for (int ronda = 0; ronda < numRondas; ++ronda) {

            shuffle(equipos.begin(), equipos.end(), g);

            for (int equipo : equipos) {
                int sede = equipo;

                bool cumpleRestricciones = true;
                if (sede == ultimaSede && consecutivasSede >= (N - d1)) {
                    cumpleRestricciones = false;
                }
                if (equipo == ultimoEquipo && consecutivasEquipo >= ((N / 2) - d2)) {
                    cumpleRestricciones = false;
                }

                if (cumpleRestricciones) {
                    rondas[ronda] = equipo;
                    if (sede == ultimaSede) consecutivasSede++;
                    else consecutivasSede = 1;

                    if (equipo == ultimoEquipo) consecutivasEquipo++;
                    else consecutivasEquipo = 1;

                    ultimaSede = sede;
                    ultimoEquipo = equipo;
                    break;
                }
            }
        }

        for (int ronda = 0; ronda < numRondas; ++ronda) {
            solucionInicial[arbitro * numRondas + ronda] = rondas[ronda];
        }
    }

    return solucionInicial;
}
