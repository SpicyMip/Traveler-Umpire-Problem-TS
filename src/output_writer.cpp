#include "output_writer.h"
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void guardarOutput(const std::string& nombreInstancia, unsigned int semilla, int distanciaTotal, int d1, int d2, const std::vector<int>& solucionInicial, int numArbitros, int numRondas) {

    fs::create_directories("output");

    std::string nombreArchivo = "output/" + nombreInstancia + "_" + std::to_string(semilla) + ".txt";

    std::ofstream archivoSalida(nombreArchivo);
    if (!archivoSalida.is_open()) {
        std::cerr << "Error al abrir el archivo de salida: " << nombreArchivo << std::endl;
        return;
    }

    archivoSalida << distanciaTotal << std::endl;

    archivoSalida << d1 << " " << d2 << std::endl;

    for (int arbitro = 0; arbitro < numArbitros; ++arbitro) {
        for (int ronda = 0; ronda < numRondas; ++ronda) {
            archivoSalida << solucionInicial[arbitro * numRondas + ronda] << " ";
        }
        archivoSalida << std::endl;
    }

    archivoSalida.close();
    std::cout << "Resultado guardado en: " << nombreArchivo << std::endl;
}
