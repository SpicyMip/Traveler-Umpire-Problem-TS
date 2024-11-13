# Traveling Umpire Problem (TUP) - Implementación en C++

## Contexto del Problema

El **Traveling Umpire Problem (TUP)** es un problema de optimización combinatoria que busca minimizar la distancia total recorrida por los árbitros asignados a diferentes sedes para supervisar partidos de un torneo. El objetivo es asignar árbitros a los partidos de manera que:
1. **Se minimice la distancia total recorrida** por cada árbitro en el torneo.
2. **Se cumplan las siguientes restricciones**:
   - Ningún árbitro puede estar en la misma sede por más de `N - d1` rondas consecutivas.
   - Ningún árbitro puede dirigir el partido del mismo equipo más de `[N/2] - d2` rondas consecutivas.
   - Cada árbitro debe visitar la sede de cada equipo al menos una vez.

En este proyecto, estamos desarrollando una solución en C++ que actualmente incluye:
1. **Lectura de Instancia**: Carga de los datos de una instancia específica del problema.
2. **Función de Evaluación**: Cálculo de la distancia total recorrida en una solución dada.
3. **Generación de Solución Inicial**: Generación de una asignación inicial de árbitros a sedes que respete las restricciones establecidas.

**Nota**: La implementación del algoritmo de optimización Búsqueda Tabú aún está en desarrollo y no se encuentra en esta versión.

---

## Estructura del Proyecto

```bash
proyecto_tup/
├── src/
│   ├── main.cpp                          # Archivo principal para ejecutar el programa
│   ├── instancia.cpp                     # Implementación de la lectura de instancia
│   ├── evaluacion.cpp                    # Implementación de la función de evaluación
│   ├── solucion_inicial.cpp              # Generación de la solución inicial
│   ├── output_writer.cpp                 # Escritura del output en un archivo de texto
├── include/
│   ├── instancia.h                       # Encabezado para la lectura de instancia
│   ├── evaluacion.h                      # Encabezado para la función de evaluación
│   ├── solucion_inicial.h                # Encabezado para la solución inicial
│   ├── output_writer.h                   # Encabezado para la escritura del output
├── data/
│   ├── [instancias]                      # Archivo de ejemplo con instancia del problema
│   ├── ...                         
├── output/
│   ├── [Nombre instancia]_[Semilla].txt  # Archivos de salida generados
│   ├── ...  
└── Makefile                              # Archivo para compilar y ejecutar el programa

```
## Ejecución
### Compilación
Para compilar el programa, asegúrate de estar en el directorio raíz del proyecto y usa el siguiente comando:

```bash
make
```
Esto generará un ejecutable llamado `proyecto_tup`.

### Ejecución del Programa
Para ejecutar el programa, usa el siguiente comando:

```bash
make run ARGS="data/umps4.txt [semilla]"
```
- `data/umps4.txt`: Especifica la ruta del archivo de instancia con los datos de entrada.
- `[semilla]` (opcional): Proporciona una semilla para generar una solución inicial reproducible. Si no se incluye, el programa utilizará el tiempo actual como semilla para generar una solución aleatoria.
### Ejemplo de Ejecución
```bash
make run ARGS="data/umps4.txt 12345"
```
### Salida del Programa
1. Consola: La ejecución muestra en consola la distancia total, los valores de `d1` y `d2`, y la matriz que representa las asignaciones de árbitros en cada ronda.

2. Archivo de salida: Además, los resultados se guardan en un archivo en la carpeta `output/` con el nombre `[Nombre instancia]_[Semilla].txt`. El formato del archivo de salida es:
```bash
[Distancia]
[d1] [d2]
[Matriz]
```
## Ejemplo de Archivo de Salida
Si el archivo de instancia es `umps4.txt` y la semilla es `12345`, el archivo `output/umps4_12345.txt` podría verse así:

```bash
5834
2 1
0 1 2 3
1 2 0 3
...
```
## Estado del Proyecto y Próximos Pasos
Actualmente, el proyecto incluye la lectura de instancia, la función de evaluación y la generación de la solución inicial, cumpliendo con las restricciones del problema. En futuras actualizaciones, se implementará el algoritmo de Búsqueda Tabú para optimizar la solución inicial y reducir la distancia total recorrida.
