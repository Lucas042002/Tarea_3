#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list.h"

#ifndef struct_h
#define struct_h

typedef struct coordenadas coordenadas;
typedef struct nombreruta nombreruta;

coordenadas *crearCoordenadas(int n,int x,int y,float distancia, int yaPaso);
void get_rutasPosibles(List *lista,int cont,coordenadas* cord);
nombreruta *crearruta(char *nombre,int *vector, int cont);
int get_x (coordenadas * n);
int get_y (coordenadas * n);
float get_distancia (coordenadas * n);
int get_yaPaso (coordenadas * n);
int get_nEntrega (coordenadas * n);

#endif /* struct_h */