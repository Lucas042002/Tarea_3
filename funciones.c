#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "struct.h"
#include "grafos.h"
#include "funciones.h"
#include "list.h"

int *generarVector(int cont){
    int *vector=malloc(sizeof(int)*cont);
    
    // Formula a + rand() % (b-a+1)
    // eligiendo 15 numeros aleatorios distintos entre 1 y 50
    for(int i=0;i<cont;i++){
    // Genera numero aleatorio
        int num = 1 + rand()%cont;

        if(i>0){
      // Verifica si no se ha generado antes   
      for(int j=0; j < i; j++)     
          if(num==vector[j]){
            num = 1 + rand()%cont;
            j=-1;                         
          }
        }
        vector [ i ] =num;
    }
    return vector;
}
float distancia(int i,int j, List * lista){
    coordenadas*aux=first(lista);
    while (aux!=NULL){
        if (get_nEntrega(aux)==i)break;
        aux=next(lista);
    }
    //printf ("aux = |x = %d |y = %d\n", get_x(aux), get_y(aux));
    coordenadas*aux2=first(lista);
    while (aux2!=NULL){
        if (get_nEntrega(aux2)==j)break;
        aux2=next(lista);
    }
    //printf ("aux2 = |x = %d |y = %d\n", get_x(aux2), get_y(aux2));
    int difX = get_x(aux)-get_x(aux2);
    int difY = get_y(aux)-get_y(aux2);
    //printf ("difX = %d | difY = %d\n",difX, difY);
    float distancia = sqrt(pow(difX,2) + pow(difY,2)); 
    //printf ("distancia = %.2f\n", distancia);
    return distancia;
}
int  ImportarArchivo(FILE *texto, List * lista){
    char *linea;
    char *ptr;
    coordenadas*cord;
    int cont = 1;
    while (!feof(texto)){
      linea = (char *) calloc(10000, sizeof(char));
      fgets(linea, 10000, texto);
      if( linea ){
        int x;
        int y;
        ptr = strtok(linea, " ");
        if( ptr ){
            x = atoi(ptr);
            ptr = strtok(NULL, ",\n");
            y = atoi(ptr);

            cord = crearCoordenadas(cont,x,y,0,0);
            pushBack(lista,cord);
            cont++;
        }
      }
    }
    return cont;
}
void crearRuta(int cont, List *lista, List *rutas){
    int x, y;
    List *lista2 = createList(); //copia de lista modificable en funcion
    List *viaje = createList();

    printf("Ingrese variable X:\n");
    scanf("%d", &x);
    printf("Ingrese variable Y:\n");
    scanf("%d", &y);
    lista2=lista;
    coordenadas*cord;
    cord = crearCoordenadas(cont,x,y,0,0);
    pushBack(lista2,cord);

    int vector [cont];
    int i = 0;
    int id;
    while (i<cont){
        get_rutasPosibles(lista2, cont,cord);
        printf("Ingrese id de la entrega:\n");
        scanf("%d", &id);
        vector[i]=id;
        coordenadas*aux=first(lista2);
        while (aux!=NULL){
            if (get_nEntrega(aux)==id){
                popCurrent(lista2);
                break;
            }
            aux=next(lista2);
        }
        coordenadas*cord;
        cord = crearCoordenadas(id,x,y,0,0);
        pushBack(viaje,cord);
        i++;
    }
    printf("guatafak\n");
    char*nombre=(char*)malloc(sizeof(char));
    printf("Ingrese nombre de la ruta:\n");
    scanf("%s", nombre);
    nombreruta*auxruta=crearruta(nombre,vector);
    pushBack(rutas,auxruta);
    clean(lista2);
    clean(viaje);
}
void crearRutaAleatoria(int cont,List* lista,List* rutas){
    int x, y;
    List *lista2 = createList();
    List *viaje = createList();

    printf("Ingrese variable X:\n");
    scanf("%d", &x);
    printf("Ingrese variable Y:\n");
    scanf("%d", &y);
    lista2=lista;
    coordenadas*cord;
    cord = crearCoordenadas(cont,x,y,0,0);
    pushBack(lista2,cord);
    int *vector;
    int i = 0;
    int id = 0;
    int cont_distancia=0;
    while (i<cont){
        vector = generarVector(cont);
        get_rutasPosibles(lista2, cont,cord);
        id=vector[i];
        coordenadas*aux=first(lista2);
        while (aux!=NULL){
            if (get_nEntrega(aux)==id){
                cont_distancia += get_distancia(aux);
                popCurrent(lista2);
                break;
            }
            aux=next(lista2);
        }
        coordenadas*cord;
        cord = crearCoordenadas(id,x,y,0,0);
        pushBack(viaje,cord);
        i++;
    }
    printf("guatafak\n");
    char*nombre=(char*)malloc(sizeof(char));
    printf("Ingrese nombre de la ruta:\n");
    scanf("%s", nombre);
    nombreruta*auxruta=crearruta(nombre,vector);
    pushBack(rutas,auxruta);
    clean(lista2);
    clean(viaje);
    for (int i = 0 ;  i < cont ;i++ ){
        printf("%d -",vector[i]);
    }
    printf("\n");
    printf("distancia = %d\n",cont_distancia);
}

