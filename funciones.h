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

typedef struct aux aux;

int *generarVector(int cont);
int ImportarArchivo(FILE *texto, List * lista);
void crearRuta(int cont, List *lista, HashMap *rutas);
float distancia(int i,int j, List * lista);
void crearRutaAleatoria(int cont, List *lista, HashMap *rutas);
void mostrarRutas(HashMap *rutas, int cont);
void mejorRuta(int cont, List *lista, HashMap *rutas, int *total_rutas);
void mejorarRuta(int cont, List *lista, HashMap *rutas);
void distancia_2puntos(List * lista);
#endif /* funciones_h */