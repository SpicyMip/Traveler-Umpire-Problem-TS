CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

TARGET = proyecto_tup

SRC = src/main.cpp src/instancia.cpp src/evaluacion.cpp src/solucion_inicial.cpp src/output_writer.cpp src/tabu_search.cpp src/utils.cpp
OBJ = $(SRC:.cpp=.o)
INC = -Iinclude

# Regla principal: compilar el proyecto
all: $(TARGET)

# Regla para generar el ejecutable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

# Regla para compilar archivos .cpp a .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INC)

# Regla para limpiar archivos compilados
clean:
	rm -f $(OBJ) $(TARGET)

# Regla para ejecutar el programa con parámetros
run: $(TARGET)
	@echo "Ejecutando $(TARGET) con parámetros:"
	@./$(TARGET) $(ARGS)
