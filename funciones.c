#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include "struct.h"
#include "funciones.h"
#include "list.h"
#include "Map.h"

int *generarVector(int cont){ 
    srand (time(NULL));
    int *vector=malloc(sizeof(int)*cont);
    vector[0]=cont;
    // Formula a + rand() % (b-a+1)
    // eligiendo cont numeros aleatorios distintos entre 1 y cont
    for(int i=1;i<cont;i++){
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
    difX = pow(difX,2);
    difY = pow(difY,2);
    float distancia = sqrt( difX + difY ); 
    //printf ("distancia = %.2f\n", distancia);
    return distancia;
}
int  ImportarArchivo(FILE *texto, List * lista){
    char *linea;
    char *ptr;
    coordenadas*cord;
    int cont = 1;
    /*int n,contLineas = 0;
    scanf ("Cuantas lineas va a leer: %d\n", n);*/
    /*|| contLineas!=n*/
    while (!feof(texto) ){
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
        //contLineas++;
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
    
    //Se copia la lista original, en una modificable
    coordenadas*auxLista=first(lista);
    while (auxLista!=NULL){
        coordenadas*aux3=crearCoordenadas(get_nEntrega(auxLista),get_x(auxLista),get_y(auxLista),get_distancia(auxLista),get_yaPaso(auxLista));
        pushBack(lista2,aux3);
        auxLista=next(lista);
    }
    //Se guarda la coordenada de inicio como la ultima de la lista modificable
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
    printf("AAAA\n");
    char*nombre=(char*)malloc(sizeof(char));
    printf("Ingrese nombre de la ruta:\n");
    scanf("%s", nombre);
    //nombreruta*auxruta=crearruta(nombre,vector);
    //pushBack(rutas,auxruta);
    clean(lista2);
    clean(viaje);
}
void crearRutaAleatoria(int cont,List* lista,HashMap* rutas){
    int x, y;
    List *lista2 = createList();
    List *viaje = createList();

    coordenadas*aux3=first(lista);
    while (aux3!=NULL){
        printf("%d -",get_nEntrega(aux3));
        aux3=next(lista);
    }
    printf("\n");

    printf("Ingrese variable X:\n");
    scanf("%d", &x);
    printf("Ingrese variable Y:\n");
    scanf("%d", &y);

    //Se copia la lista original, en una modificable
    coordenadas*auxLista=first(lista);
    while (auxLista!=NULL){
        coordenadas*aux3=crearCoordenadas(get_nEntrega(auxLista),get_x(auxLista),get_y(auxLista),get_distancia(auxLista),get_yaPaso(auxLista));
        pushBack(lista2,aux3);
        auxLista=next(lista);
    }
   
    //Se guarda la coordenada de inicio como la ultima de la lista modificable
    coordenadas*cord;
    cord = crearCoordenadas(cont,x,y,0,0);
    pushBack(lista2,cord);
    
    int *vector,i = 0,id = 0;
    float cont_distancia=0;
    vector = generarVector(cont);

    for (int i = 0 ;  i < cont ;i++ ){
        if (i==cont-1)  printf("%d",vector[i]);
        else printf("%d -> ",vector[i]);
    }
    
    while (i<cont){
        printf("\n");
        printf("CORD: numero id = %d\n",get_nEntrega(cord));
        get_rutasPosibles(lista2, cont ,cord);
        id=vector[i];
        coordenadas*aux=first(lista2);
        while (aux!=NULL){
            if (get_nEntrega(aux)==id){
                popCurrent(lista2);
                printf("lel\n");
                break;
            }
            aux=next(lista2);
        }
        if (i==cont-1){
            coordenadas*cordAux = crearCoordenadas(id,get_x(cord),get_y(cord),get_distancia(cord),0);
            pushBack(viaje,cordAux);
        }
        i++;
        id=vector[i];
        coordenadas*aux2=first(lista2);
        while (aux2!=NULL){
            if (get_nEntrega(aux2)==id){
                coordenadas*cordAux = crearCoordenadas(vector[i-1],get_x(cord),get_y(cord),get_distancia(aux2),0);
                pushBack(viaje,cordAux);
                cord = aux2;
                cont_distancia += get_distancia(cord);
                printf("Distancia elegida = %.2f\n",get_distancia(cord));
                break;
            }
            aux2=next(lista2);
        }
    }

    char*nombre=(char*)malloc(sizeof(char));
    printf("Ingrese nombre de la ruta:\n");
    scanf("%s", nombre);

    printf("\n");
    printf("Distancia recorrida = %.2f\n",cont_distancia);

    coordenadas*aux2=first(viaje);
    while (aux2!=NULL){
        printf("%.2f ",get_distancia(aux2));
        aux2=next(viaje);
    }
    printf("\n");
    insertMap(rutas,nombre,viaje);
    
    clean(lista2);
    clean(viaje);
    free(vector);
    free(nombre);
    free(cord);
    
}
void mostrarRutas(HashMap *rutas){
    printf("Aun no hay ninguna ruta ingresada.\n");
    if (rutas == NULL){
        printf("Aun no hay ninguna ruta ingresada.\n");
        return;
    }
    List*viaje=firstMap(rutas);
    coordenadas*aux1=first(viaje);
    printf("%d - ", get_nEntrega(aux1));
    while (aux1!=NULL){
        printf("%d - ", get_nEntrega(aux1));
        aux1=next(viaje);
    }
    /*while (aux!=NULL){
        
        aux=nextMap(rutas);
    }*/
}

