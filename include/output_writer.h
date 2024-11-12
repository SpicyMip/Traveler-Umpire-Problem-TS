#ifndef OUTPUT_WRITER_H
#define OUTPUT_WRITER_H

#include <string>
#include <vector>
#include "instancia.h"

void guardarOutput(const std::string& nombreInstancia, unsigned int semilla, int distanciaTotal, int d1, int d2, const std::vector<int>& solucionInicial, int numArbitros, int numRondas);

#endif
