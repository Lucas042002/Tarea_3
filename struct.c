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
        if (aux->yaPaso==0){ 
            aux->distancia = distancia (cord->numeroEntrega, aux->numeroEntrega, lista);
            vector[i]=aux;
            i++;
        }
        aux=next(lista);
    }
    
    coordenadas *swap;
    for (int c = 0 ; c < i-1 ; c++){
        for (int d = 0 ; d < i - c-1; d++){
            
            if (vector[d]->distancia > vector[d+1]->distancia){
                swap       = vector[d];
                vector[d]   = vector[d+1];
                vector[d+1] = swap;
                
            }
        }
    }
    printf("DISTANCIA\tID\n");
    printf("----------------------\n");
    for (int k=0;k<i;k++){
        if ((vector[k]->yaPaso)==0 && vector[k]->distancia!=0){
            printf ("%.2f\t\t%d\n",vector[k]->distancia, vector[k]->numeroEntrega);
        }
    }
     printf("\n");   
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

void modificarYapaso( coordenadas *aux){
    aux->yaPaso=1;
}

void entregasCercanas (List* lista, int cont){
    
    int x, y;
    List *lista2 = createList(); //copia de lista modificable en funcion
    

    printf("Ingrese variable X:\n");
    scanf("%d", &x);
    printf("Ingrese variable Y:\n");
    scanf("%d", &y);
    printf("\n\n");
    //Se copia la lista original, en una modificable
    coordenadas*auxLista=first(lista);
    while (auxLista!=NULL){
        coordenadas*aux3=crearCoordenadas(get_nEntrega(auxLista),get_x(auxLista),get_y(auxLista),get_distancia(auxLista),0);
        pushBack(lista2,aux3);
        auxLista=next(lista);
    }
    //Se guarda la coordenada de inicio como la ultima de la lista modificable
    coordenadas*cord;
  
    cord = crearCoordenadas(cont,x,y,0,0);
    pushBack(lista2,cord);
 
    coordenadas*aux= first(lista2);
    coordenadas**vector= malloc(sizeof(coordenadas)*cont);
    int i=0;
    
    while (aux!=NULL){
         
            aux->distancia = distancia (cord->numeroEntrega, aux->numeroEntrega, lista2);
           
            vector[i]=aux;
             
           i++;
        
        aux=next(lista2);
    }
    
    coordenadas *swap;
    for (int c = 0 ; c < i -1; c++){
        for (int d = 0 ; d < i- c-1; d++){
            if (vector[d]->distancia > vector[d+1]->distancia){
                swap       = vector[d];
                vector[d]   = vector[d+1];
                vector[d+1] = swap;   
            }
        }
    }
    
printf("DISTANCIA\tID\n");
printf("\n");
    for (int k=1;k<4;k++){
        
            printf ("%.2f\t\t%d\n",vector[k]->distancia, vector[k]->numeroEntrega);
        
    }
}

