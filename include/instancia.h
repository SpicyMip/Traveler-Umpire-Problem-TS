#ifndef INSTANCIA_H
#define INSTANCIA_H

#include <vector>
#include <string>

struct InstanciaTUP {
    int numArbitros;
    std::vector<std::vector<int>> matrizDistancias;
    std::vector<std::vector<int>> matrizRondas;
};

InstanciaTUP leerInstancia(const std::string& archivo);

#endif
