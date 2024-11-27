#include "solucion_inicial.h"
#include "utils.h"
#include <algorithm>
#include <random>
#include <set>
#include <ostream>
#include <iostream>

using namespace std;

vector<int> generarSolucionInicial(const InstanciaTUP& instancia, int N, int d1, int d2, unsigned int semilla) {
    int numRondas = instancia.matrizRondas.size(); // Rondas totales
    int numEquipos = 2 * N;
    int numJuegosPorRonda = numEquipos / 2;

    vector<int> solucionInicial(N * numRondas, -1);

    mt19937 g(semilla);

    // Crear lista de juegos por ronda
    vector<vector<int>> juegosPorRonda(numRondas);
    for (int ronda = 0; ronda < numRondas; ++ronda) {
        // Cada ronda tiene numJuegosPorRonda juegos
        for (int juego = 0; juego < numJuegosPorRonda; ++juego) {
            juegosPorRonda[ronda].push_back(juego);
        }
    }

    // Asignar árbitros a juegos en cada ronda
    for (int arbitro = 0; arbitro < N; ++arbitro) {
        int consecutivasSede = 1;
        int consecutivasEquipo = 1;
        int ultimaSede = -1;
        int ultimoEquipo = -1;

        for (int ronda = 0; ronda < numRondas; ++ronda) {
            vector<int>& juegosDisponibles = juegosPorRonda[ronda];

            // Desordenar los juegos disponibles
            shuffle(juegosDisponibles.begin(), juegosDisponibles.end(), g);

            bool asignado = false;
            for (int juego : juegosDisponibles) {
                int equipoLocal, equipoVisitante;
                obtenerEquiposDelJuego(instancia, ronda, juego, equipoLocal, equipoVisitante);
                int sede = equipoLocal; // La sede es el equipo local

                // Verificar restricciones de sede y equipo
                bool cumpleRestricciones = true;
                if (sede == ultimaSede && consecutivasSede >= (N - d1)) {
                    cumpleRestricciones = false;
                }

                // Verificar para ambos equipos (local y visitante)
                bool mismoEquipo = (equipoLocal == ultimoEquipo) || (equipoVisitante == ultimoEquipo);
                if (mismoEquipo && consecutivasEquipo >= ((N / 2) - d2)) {
                    cumpleRestricciones = false;
                }

                if (cumpleRestricciones) {
                    // Asignar el juego al árbitro
                    solucionInicial[arbitro * numRondas + ronda] = juego;

                    // Actualizar variables
                    if (sede == ultimaSede) consecutivasSede++;
                    else {
                        consecutivasSede = 1;
                        ultimaSede = sede;
                    }

                    if (equipoLocal == ultimoEquipo || equipoVisitante == ultimoEquipo) {
                        consecutivasEquipo++;
                    } else {
                        consecutivasEquipo = 1;
                        // Puedes elegir actualizar a cualquiera de los dos equipos
                        ultimoEquipo = equipoLocal; // O equipoVisitante
                    }

                    // Remover el juego de los disponibles
                    juegosDisponibles.erase(remove(juegosDisponibles.begin(), juegosDisponibles.end(), juego), juegosDisponibles.end());
                    asignado = true;
                    break;
                }
            }

            if (!asignado) {
                // No se pudo asignar un juego cumpliendo restricciones
                // Asignar cualquier juego disponible
                if (!juegosDisponibles.empty()) {
                    int juego = juegosDisponibles.back();
                    juegosDisponibles.pop_back();

                    // Asignar el juego al árbitro
                    solucionInicial[arbitro * numRondas + ronda] = juego;

                    // Actualizar variables
                    int equipoLocal, equipoVisitante;
                    obtenerEquiposDelJuego(instancia, ronda, juego, equipoLocal, equipoVisitante);
                    int sede = equipoLocal;

                    if (sede == ultimaSede) consecutivasSede++;
                    else {
                        consecutivasSede = 1;
                        ultimaSede = sede;
                    }

                    // Actualizar el último equipo (puedes elegir local o visitante)
                    ultimoEquipo = equipoLocal; // O equipoVisitante
                    consecutivasEquipo = 1; // Reinicia el contador
                } else {
                    // No hay juegos disponibles en esta ronda, esto no debería ocurrir
                    cerr << "Error: No hay juegos disponibles para asignar al árbitro " << arbitro << " en la ronda " << ronda << endl;
                    return {}; // Retornar solución vacía o manejar el error según convenga
                }
            }
        }
    }

    return solucionInicial;
}
