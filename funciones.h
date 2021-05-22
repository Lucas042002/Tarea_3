#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "struct.h"
#include "grafos.h"
#include "list.h"

#ifndef funciones_h
#define funciones_h

int *generarVector(int cont);
int ImportarArchivo(FILE *texto, List * lista);
void crearRuta(int cont, List *lista, List *rutas);
float distancia(int i,int j, List * lista);
void crearRutaAleatoria(int cont, List *lista, List *rutas);


#endif /* funciones_h */