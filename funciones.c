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
void crearRuta(int cont, List *lista, HashMap *rutas){
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
    cord = crearCoordenadas(cont,x,y,0,1);
    pushBack(lista2,cord);

    int vector [cont];
    int i = 0;
    int id;
    float cont_distancia=0;
    
    while (i<cont-1){
        get_rutasPosibles(lista2, cont,cord);
        
        printf("Ingrese id de la entrega:\n");
        scanf("%d", &id);
        vector[i]=id;
        coordenadas*aux=first(lista2);
        while (aux!=NULL){
            if (get_nEntrega(aux)==id){
                coordenadas*cordAux = crearCoordenadas(get_nEntrega(cord),get_x(cord),get_y(cord),get_distancia(aux),1);
                pushBack(viaje,cordAux);
                modificarYapaso(aux);
                cord=crearCoordenadas(get_nEntrega(aux),get_x(aux),get_y(aux),0,1);
                cont_distancia += get_distancia(aux);
                printf("Distancia elegida = %.2f\n",get_distancia(aux));
                printf("\n");
                break;
            }
            aux=next(lista2);
        }

        i++;
        if (i==cont-1){
            coordenadas*cordAux = crearCoordenadas(id,get_x(cord),get_y(cord),get_distancia(cord),0);
            pushBack(viaje,cordAux);
        }
    }
    char*nombre=(char*)malloc(sizeof(char));
    printf("Ingrese nombre de la ruta:\n");
    scanf("%s", nombre);
    coordenadas* ultima= crearCoordenadas(0,0,0, cont_distancia, 0);
    pushBack(viaje, ultima);
    printf("\n");
    printf("Distancia recorrida = %.2f\n",cont_distancia);

    printf("\n");
    
    insertMap(rutas,nombre,viaje);
    
    clean(lista2);
    free(vector);
    free(cord);
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
    //inserta la distancia total recorrida de la ruta y la guarda en la lista y luego en el mapa
    coordenadas* ultima= crearCoordenadas(0,0,0, cont_distancia, 0);
    pushBack(viaje, ultima);
    printf("\n");
    insertMap(rutas,nombre,viaje);
    
    clean(lista2);
    free(vector);
    free(cord);
    
}
void mostrarRutas(HashMap* rutas, int cont){
    if (rutas == NULL){
        printf("Aun no hay ninguna ruta ingresada.\n");
        return;
    }
     printf("0\n");
    BubbleSort(rutas);
     printf("1\n");
    List *viaje=firstMap(rutas);
    printf("2\n");
    while(viaje!=NULL){
        coordenadas*aux1=first(viaje);
        float cont_distancia2=0;
        while (aux1!=NULL){
            cont_distancia2+=get_distancia(aux1);
            printf("%d-",get_nEntrega(aux1));
            aux1=next(viaje);
        }
        printf("%.2f-",cont_distancia2);
        printf("\n");
      viaje=nextMap(rutas);
    }  
}
void BubbleSort(HashMap *ruta){
  if (ruta==NULL) return;
  if(get_size(ruta)==0) return;
    List* ptr1;
    List* lptr=NULL;
    int swapped;
    do{
        swapped = 0;
        ptr1 = firstMap(ruta);
        printf("3\n");
        while (nextMap(ruta) != lptr){
            printf("3.1a\n");
          coordenadas* aux;
          coordenadas*aux2;
          printf("3.1\n");
          int i=0;
          while(i<get_size(ptr1)){
            aux=next(ptr1);
              printf("4\n");
            aux2=next(nextMap(ruta));
                printf("4.2\n");
            i++;
          }
            if (get_distancia(aux) > get_distancia(aux2))
            { 
                List* temp = createList();
                coordenadas* auxCoord = first(ptr1);
                while(ptr1!=NULL) {
                  pushBack(temp, auxCoord);
                  auxCoord=next(ptr1);
                }
                
                List* temp2 = createList();
                coordenadas* auxCoord2 = first(ptr1);
                while(next(ptr1)!=NULL) {
                  pushBack(temp2, auxCoord2);
                  auxCoord2=next(next(ptr1));
                }
                ptr1 = temp2;
                List*sgte = next(ptr1);
                sgte = temp;
                swapped = 1;
            }
            ptr1 = nextMap(ruta);
        }
        lptr = ptr1;
    }while (swapped!=0);
}


