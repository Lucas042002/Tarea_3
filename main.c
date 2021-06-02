#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "struct.h"
#include "funciones.h"
#include "list.h"
#include "Map.h"

int main (){
    FILE * texto = fopen ("tarea3_tsp.txt", "r");
    List * lista = createList();
    HashMap * rutas;
    int cont = 0;
    int numero = -1;
    while(numero != 0){
        
        printf("-----------------------------------------\n");
        printf("                MENU\n");
        printf("-----------------------------------------\n");
        printf("1.- Importar Archivo Coordenadas\n");
        printf("2.- Distancia entre entregas\n");
        printf("3.- Mostrar 3 entregas más cercanas \n");
        printf("4.- Crear ruta \n");
        printf("5.- Generar ruta aleatoria\n");
        printf("6.- Mejorar ruta \n");
        printf("7.- Mostrar rutas\n");
        printf("8.- Mejor ruta\n");
        printf("0.- Salir\n");
        printf("\n");
        printf("Indica la opcion: ");

        scanf("%d", &numero);

        printf("\n");

        switch(numero){
            case 1: {
                cont=ImportarArchivo(texto,lista); 
                float matriz[cont][cont];
                for (int i=1;i<cont;i++){
                    for(int j=1;j<cont;j++){
                        matriz[i][j]=distancia(i,j,lista);
                    }
                }
                rutas=createMap(cont);  
                break;
                
            }
            case 2: break;
            case 3: break;
            case 4: /*crearRuta(cont, lista, rutas); */break;
            case 5: crearRutaAleatoria(cont, lista, rutas);break;
            case 6: break;
            case 7: mostrarRutas(rutas); break;
            case 8: break;
            case 0: break;
            default: printf("Opcion no valida.\n"); break;
        }
        
    }
    return 0;
}