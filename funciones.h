#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "struct.h"
#include "list.h"
#include "Map.h"

#ifndef funciones_h
#define funciones_h

int *generarVector(int cont);
int ImportarArchivo(FILE *texto, List * lista);
void crearRuta(int cont, List *lista, HashMap *rutas);
float distancia(int i,int j, List * lista);
void crearRutaAleatoria(int cont, List *lista, HashMap *rutas);
void mostrarRutas(HashMap *rutas, int cont);
void BubbleSort(HashMap *ruta);

#endif /* funciones_h */