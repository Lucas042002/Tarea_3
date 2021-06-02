#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "struct.h"
#include "funciones.h"
#include "list.h"

typedef struct coordenadas coordenadas;
typedef struct nombreruta nombreruta;

struct nombreruta{
  char *nombreRuta;
  int *vector;
};

struct coordenadas{
  int numeroEntrega;
  int x; //coordenada x
  int y; //coordenada y
  float distancia; //para saber las distancias entre 2 puntos
  int yaPaso; // si ya se paso por el punto es igual a 1, si no es asi un 0
};

void get_rutasPosibles(List *lista,int cont,coordenadas* cord){
    coordenadas*aux= first(lista);
    coordenadas**vector = malloc (sizeof(coordenadas)*cont);
    int i=0;
    while (aux!=NULL){
        if (aux->yaPaso ==0){ 
            aux->distancia = distancia (cord->numeroEntrega, aux->numeroEntrega, lista);
            aux->yaPaso==1;
            vector[i]=aux;
            i++;
        }
        aux=next(lista);
    }
    
    /*coordenadas *swap;
    for (int c = 0 ; c < i-1 ; c++){
        for (int d = 0 ; d < i - c-1; d++){
            
            if (vector[d]->distancia > vector[d+1]->distancia){
                swap       = vector[d];
                vector[d]   = vector[d+1];
                vector[d+1] = swap;
                
            }
        }
    }*/

    for (int k=0;k<i;k++){
        printf ("distancia %.2f - id = %d\n",vector[k]->distancia, vector[k]->numeroEntrega);
    }
        
    free(vector);

}

nombreruta *crearruta(char *nombre,int *vector,int cont){
  nombreruta *ruta = (nombreruta *) malloc (sizeof(nombreruta));
  strcpy(ruta->nombreRuta,nombre);
  ruta->vector = malloc(sizeof(int)*cont);
  ruta->vector=vector;
  return ruta;
}

coordenadas *crearCoordenadas(int n,int x,int y,float distancia, int yaPaso){
  coordenadas *cord = (coordenadas *) malloc (sizeof(coordenadas));
  cord->numeroEntrega = n;
  cord->x = x;
  cord->y = y;
  cord->distancia = distancia;
  cord->yaPaso = yaPaso;
  return cord;
}

int get_nEntrega (coordenadas * n){
    return n->numeroEntrega;
}

int get_x (coordenadas * n){
    return n->x;
}
int get_y (coordenadas * n){
    return n->y;
}
float get_distancia(coordenadas * n){
    return n->distancia;
}
int get_yaPaso (coordenadas * n){
    return n->yaPaso;
}



