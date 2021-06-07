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

typedef struct aux{
    float distancia;
    int vec[100];
    char *nombre;
}aux;

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
    //recorro la lista en buscando los puntos i,j para sacar la distancia entre ellos
    while (aux!=NULL){
        if (get_nEntrega(aux)==i)break;
        aux=next(lista);
    }
    coordenadas*aux2=first(lista);
    while (aux2!=NULL){
        if (get_nEntrega(aux2)==j)break;
        aux2=next(lista);
    }
    //extraigo las variables x e y de cada punto y se aplica la formula de distancia entre 2 puntos
    int difX = get_x(aux)-get_x(aux2);
    int difY = get_y(aux)-get_y(aux2);
    difX = pow(difX,2);
    difY = pow(difY,2);
    float distancia = sqrt( difX + difY ); 
    return distancia;
}
int  ImportarArchivo(FILE *texto, List * lista){
    char *linea;
    char *ptr;
    coordenadas*cord;
    int cont = 1;
    int n,contLineas = 0;
    printf("Ingrese cantidad de Entregas a leer: ");
    scanf ("%d", &n);
    printf("\n");
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
            if (cont==n+1)break;
        }
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
    printf("\n");
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
    /*Para este codigo, lo que hace la funcion get_rutasPosibles, obtiene todas las distancias de los nodos cercanos a nuestro inicio y las modifica
    en la lista 2. Luego el usuario elige a que entrega ir, y el cord que se usa a modo de "entrega actual" o "donde esta ubicados", se actualiza para
    seguir obteniendo los nodos adyacentes. en la Lista viaje se guarda la ruta que va realizando, y el vector se ocupa a modo de registrar la ruta en 
    orden*/
    while (i<cont-1){
        get_rutasPosibles(lista2, cont,cord);
        
        printf("Ingrese id de la entrega:\n");
        scanf("%d", &id);
        printf("\n");
        vector[i]=id;
        coordenadas*aux=first(lista2);
        while (aux!=NULL){
            if (get_nEntrega(aux)==id){
                coordenadas*cordAux = crearCoordenadas(get_nEntrega(cord),get_x(cord),get_y(cord),get_distancia(aux),1);
                pushBack(viaje,cordAux);
                modificarYapaso(aux);
                cord=crearCoordenadas(get_nEntrega(aux),get_x(aux),get_y(aux),0,1);
                cont_distancia += get_distancia(aux);
                printf("Distancia elegida = %.2f.\n",get_distancia(aux));
                printf("\n");
                break;
            }
            aux=next(lista2);
        }
        i++;
        //Esta condicion sirve para insertar el ultimo nodo de la ruta generada, que sera en la ultima iteracion.
        if (i==cont-1){
            coordenadas*cordAux = crearCoordenadas(id,get_x(cord),get_y(cord),get_distancia(cord),0);
            pushBack(viaje,cordAux);
        }
    }
    char*nombre=(char*)malloc(sizeof(char));
    printf("Ingrese nombre de la ruta:\n");
    scanf("%s", nombre);
    printf("\n");
    printf("Distancia recorrida total= %.2f.\n",cont_distancia);

    printf("\n");
    
    insertMap(rutas,nombre,viaje);
    
    clean(lista2);
    free(vector);
    free(cord);
}

void crearRutaAleatoria(int cont,List* lista,HashMap* rutas){
    //Se reserva memoria a variables a usar, y listas
    int x, y;
    List *lista2 = createList(); 
    List *viaje = createList();//Sera donde se guarde el viaje que realizo la persona

    printf("\n");
    printf("\n");
    printf("Ingrese variable X:\n");
    scanf("%d", &x);
    printf("Ingrese variable Y:\n");
    scanf("%d", &y);
    printf("\n");
    //Se copia la lista original, en una modificable
    coordenadas*auxLista=first(lista);
    while (auxLista!=NULL){
        coordenadas*aux3=crearCoordenadas(get_nEntrega(auxLista),get_x(auxLista),get_y(auxLista),get_distancia(auxLista),0);
        pushBack(lista2,aux3);
        auxLista=next(lista);
    }
   
    //Se guarda la coordenada de inicio como la ultima de la lista modificable
    coordenadas*cord;
    cord = crearCoordenadas(cont,x,y,0,1);
    pushBack(lista2,cord);
    
    int *vector,i = 0,id = 0;
    float cont_distancia=0;
    /*Esta funcion genera un vector, con inicio en la entrega 6, que en este caso es la primera entrega. 
    De ahi es aleatorio el orden de las siguientes entregas sin repeticion*/
    vector = generarVector(cont);
    //Se muestra este vector.
    printf("\n");
    printf("Ruta aleatoria generada:\n");
    for (int i = 1 ;  i < cont;i++ ){
        if (i==cont-1)  printf("%d\n", vector[i]);
        else printf("%d -> ", vector[i]);
    }
    printf("\n");

    while (i<cont-1){
        /*A partir de la lista2 (que es una copia de la lista original de puntos), se obtienen las distancias, siendo cord la ubicacion 
        actual de la persona. Desde el punto inicial entonces se generan distintas posibilidades*/
        get_rutasPosibles(lista2, cont ,cord);
        /*Para moverse al siguiente punto, lo que primero hacemos es eliminar el punto de donde estamos ubicados a las posibilidades de las
        siguientes distancias*/
        id=vector[i];
        coordenadas*aux=first(lista2);
        while (aux!=NULL){
            if (get_nEntrega(aux)==id){
                modificarYapaso(aux);
                popCurrent(lista2);
                break;
            }
            aux=next(lista2);
        }
        //Esta condicion sirve para insertar el ultimo nodo de la ruta generada a partir del vector
        if (i==cont-1){
        coordenadas*cordAux = crearCoordenadas(id,get_x(cord),get_y(cord),get_distancia(cord),1);
            pushBack(viaje,cordAux);
        }
        i++;
        /*En esta parte lo que se hace es avanzar al cord (que como se dijo antes es donde uno esta actualmente) al siguiente punto del vector generado y asi
        avanzando por este hasta que se terminen las entregas*/
        id=vector[i];
        coordenadas*aux2=first(lista2);
        while (aux2!=NULL){
            if (get_nEntrega(aux2)==id){
                coordenadas*cordAux = crearCoordenadas(vector[i-1],get_x(cord),get_y(cord),get_distancia(aux2),1);
                pushBack(viaje,cordAux);
                cord = aux2;
                cont_distancia += get_distancia(cord);
                printf("Distancia elegida = %.2f.\n",get_distancia(cord));
                break;
            }
            aux2=next(lista2);
        }
        
        printf("ID posicion actual: %d\n",get_nEntrega(cord));
        printf("\n");
    }

    char*nombre=(char*)malloc(sizeof(char));
    printf("Ingrese nombre de la ruta:\n");
    scanf("%s", nombre);

    printf("\n");
    printf("Distancia total recorrida = %.2f.\n",cont_distancia);
    printf("\n");
    insertMap(rutas,nombre,viaje);
    
    clean(lista2);
    free(vector);
    free(cord);
    
}
void mostrarRutas(HashMap* rutas, int cont){
    if (rutas == NULL || get_size(rutas)==0){
        printf("Aun no hay ninguna ruta ingresada.\n");
        return;
    }
    //asigno memoria de tipo aux (aux es la struct enviada)
    aux *vectorAux=malloc(sizeof(aux)*cont);
    //se copian las rutas guardadas en un mapa en un list para avanzar por este
    List*viaje=firstMap(rutas);
    int i=0;
    //vector aux que guarda las ciudades por casilla ej: vector[0]=ciudad 6;
    int vector[cont];
    //variable que acumula la distancia entre ciudades
    float cont_dist;
    while(viaje!=NULL){
        cont_dist=0;
        coordenadas*aux1=first(viaje);     
        int j=0;
        while (aux1!=NULL){
            //getnEntrega retorna la ciudad donde se encuentra el aux1 que es como la "persona"
            vector[j]=get_nEntrega(aux1);
            cont_dist+=get_distancia(aux1);
            aux1=next(viaje);
            j++; 
        }
        //for que copia ciudad por ciudad en la struct que guarda los valores de la ruta
        for(int l=0;l<j;l++){
            vectorAux[i].vec[l]=vector[l];
        }
        //copia la distancia y nombre del vector[i] en la struct 
        vectorAux[i].nombre=get_key(rutas);
        vectorAux[i].distancia=cont_dist;
        //aumento la posicion del vector para guardar una 2da ruta
        i++;
        //avanzo en el mapa
        viaje=nextMap(rutas);
    }
    //bubblesort que ordena de menor a mayor
    aux swap;
    for (int c = 0 ; c < i-1 ; c++){
        for (int d = 0 ; d < i - c-1; d++){
            if (vectorAux[d].distancia > vectorAux[d+1].distancia){
                swap       = vectorAux[d];
                vectorAux[d]   = vectorAux[d+1];
                vectorAux[d+1] = swap;
            }
        }
    }
    //imprime los valores de las rutas 
    printf("NOMBRE\t\t\tRUTA\t\t\tDISTANCIA\n");
    for (int k=0;k<i; k++){
        
        printf("%s\t  ", vectorAux[k].nombre);
        
        for(int c =0; c<cont-1; c++){
            printf("%d /", vectorAux[k].vec[c]);
        }
        printf("\t");
        printf("%.2f ", vectorAux[k].distancia);
        printf("\n");
    }
    
}

void mejorarRuta(int cont, List *lista, HashMap *rutas){
    if (rutas == NULL || get_size(rutas)==0){
        printf("Aun no hay ninguna ruta ingresada.\n");
        return;
    }
    
    mostrarRutas(rutas, cont);
    List *lista2 = createList();
    List *viaje = createList();
    //Se copia la lista original, en una modificable
    coordenadas*auxLista=first(lista);
    while (auxLista!=NULL){
        coordenadas*aux3=crearCoordenadas(get_nEntrega(auxLista),get_x(auxLista),get_y(auxLista),get_distancia(auxLista),0);
        pushBack(lista2,aux3);
        auxLista=next(lista);
    }
    char*name=(char*)malloc(sizeof(char)); 
    printf("Indique nombre de la ruta:\n");
    scanf ("%s", name);
    List*listaSeleccionada=searchMap(rutas,name);
    //Obtener un vector con el orden de las entregas
    int *vector=malloc(sizeof(int)*cont);
    int i=0,xxyy,nEntrega1, nEntrega2;
    float distancia_original=0;

    coordenadas*aux=first(listaSeleccionada);
    while (aux!=NULL){
        vector[i] = get_nEntrega(aux);
        distancia_original += get_distancia(aux);
        aux=next(listaSeleccionada);
        i++;
    }
    
    do{
        printf("Quiere hacer un cambio manual o automatico, si es manual ingrese 0, por otro lado ingrese 1.\n");
        scanf("%d",&xxyy);
        if (xxyy==1 || xxyy ==0) break;

    }while(1==0);
    /*Lo que se hace aca, es simplemente un cambio al vector original que describia el viaje, por lo que se uso el mismo codigo que en la funcion
    crearRutaAleatoria*/
    if (xxyy==0){
        //Si el cambio es manual, se piden las entregas a cambiar
        printf("Indique entregas a cambiar.\n");
        printf("Entrega 1:\n");
        scanf("%d",&nEntrega1);
        printf("Entrega 2:\n");
        scanf("%d",&nEntrega2);
        //Cambiar las entregas
        int idx1=0,idx2=0;
        for(int i=0;i<cont;i++){
            if (vector[i]==nEntrega1){
                idx1=i;
            }
            if (vector[i]==nEntrega2){
                idx2=i;
            }
        }
        vector[idx1]=nEntrega2;
        vector[idx2]=nEntrega1;
        for (int i = 0 ;  i < cont ;i++ ){
            if (i==cont-1)  printf("%d",vector[i]);
            else printf("%d -> ",vector[i]);
        }
        printf("\n");
    }
    else{
        //Si el cambio es automatico, la maquina genera los numeros con ciertas condiciones
        srand (time(NULL));
        int swap;
        do{
            nEntrega1=1+rand()%(cont-1);
            nEntrega2=1+rand()%(cont-1);
            if (nEntrega1!=nEntrega2 && nEntrega2!=0 && nEntrega1!=0) break;

        }while(1==0);
        int idx1=0,idx2=0;
        for(int i=0;i<cont;i++){
            if (vector[i]==nEntrega1){
                idx1=i;
            }
            if (vector[i]==nEntrega2){
                idx2=i;
            }
        }
        vector[idx1]=nEntrega2;
        vector[idx2]=nEntrega1;
        for (int i = 0 ;  i < cont ;i++ ){
            if (i==cont-1)  printf("%d",vector[i]);
            else printf("%d -> ",vector[i]);
        }
        printf("\n");
    }
    
    //Genero el viaje con las entregas cambiadas, a partir de aca es el mismo codigo que anteriormente mencionamos, que genera la ruta a partir de un vector
    float cont_distancia=0;
    int id;
    coordenadas*aux2=first(listaSeleccionada);
    coordenadas*cord=crearCoordenadas(get_nEntrega(aux2),get_x(aux2),get_y(aux2),0,0);
    pushBack(lista2,cord);
    i=0;
    while (i<cont){
        get_rutasPosibles(lista2,cont,cord);
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
                coordenadas*cordAux = crearCoordenadas(vector[i-1],get_x(cord),get_y(cord),get_distancia(aux2),1);
                pushBack(viaje,cordAux);
                cord = aux2;
                cont_distancia += get_distancia(cord);
                printf("Distancia elegida = %.2f\n",get_distancia(cord));
                printf("\n");
                break;
            }
            aux2=next(lista2);
        }
    }
    //Muestro por pantalla los cambios
    printf("Distancia recorrida de la nueva ruta = %.2f\n",cont_distancia);
    printf("Distancia recorrida original = %.2f\n",distancia_original);
    //Dependiendo de lo que sea se elije el mensaje.
    if (distancia_original<=cont_distancia){
        printf("La ruta original sigue siendo mas eficiente, no se hicieron cambios.\n");
    }
    else{
        eraseMap(rutas,name);
        insertMap(rutas,name,viaje);
        printf("Se cambio el orden de la ruta exitosamente.\n");
    }
    coordenadas*aux3=first(viaje);
    i=0;
    while (aux3!=NULL){
        if (i==cont-1)printf("%d",get_nEntrega(aux3));
        else printf("%d -> ",get_nEntrega(aux3));
        aux3=next(viaje);
        i++;
    }
    printf("\n");
}
void mejorRuta(int cont, List *lista, HashMap *rutas, int *total_rutas){
    int x, y, z=0;
    List *lista2 = createList(); //copia de lista modificable en funcion
    List *viaje = createList();

    printf("Ingrese variable X:\n");
    scanf("%d", &x);
    printf("Ingrese variable Y:\n");
    scanf("%d", &y);
    
    //Se copia la lista original, en una modificable
    coordenadas*auxLista=first(lista);
    while (auxLista!=NULL){
        coordenadas*aux3=crearCoordenadas(get_nEntrega(auxLista),get_x(auxLista),get_y(auxLista),get_distancia(auxLista),0);
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
    float cont_distancia=0,menor_dist=0;
    /*Para esta funcion reciclamos el codigo utilizado en la opcion 4 de crear ruta, la diferencia es que aca se crea la ruta en base a la menor distancia
    entre los nodos. Por lo que en cada situacion se ubica la id que representa el numero de entrega, mas cercano al cord, la posicion. Verificando que sea
    la menor y ademas que no se haya pasado.*/
    while (i<cont-1){
        get_rutasPosibles(lista2, cont,cord);
        coordenadas*aux1=first(lista2);
        menor_dist=get_distancia(aux1);
        while (aux1!=NULL){
            if (get_yaPaso(aux1)==0){
                if (menor_dist>get_distancia(aux1) && menor_dist!=0 && get_nEntrega(aux1)!=cont){
                    menor_dist=get_distancia(aux1);
                    id=get_nEntrega(aux1);
                }
            }
            aux1=next(lista2);
        }
        
        vector[i]=id;
        coordenadas*aux=first(lista2);
        while (aux!=NULL){
            if (get_nEntrega(aux)==id){
                coordenadas*cordAux = crearCoordenadas(get_nEntrega(cord),get_x(cord),get_y(cord),get_distancia(aux),1);
                pushBack(viaje,cordAux);
                modificarYapaso(aux);
                
                cord=crearCoordenadas(get_nEntrega(aux),get_x(aux),get_y(aux),0,1);
                cont_distancia += get_distancia(aux);
                printf("Distancia elegida = %.2f.\n",get_distancia(aux));
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
    //Usamos una variable externa int que se va modificando a nivel de todo el codigo de manera que se van guardando con el nombre pedido y el numero.
    z++;
    *total_rutas+=z;
    char*rutaoptima=(char*)malloc(sizeof(char)*20);
    char *numerin;
    strcpy (rutaoptima,"Ruta_Optima_");
    itoa(*total_rutas,numerin,10);
    strcat (rutaoptima,numerin);

    printf("Viaje guardado como %s.",rutaoptima);
    printf("\n");
    printf("Distancia recorrida = %.2f.\n",cont_distancia);
    printf("\n");
    
    insertMap(rutas,rutaoptima,viaje);
    
    clean(lista2);
    free(vector);
    free(cord);
}

void distancia_2puntos(List * lista){
    coordenadas*auxMostrar=first(lista);
    printf("id\tX\tY\n");
    while (auxMostrar!=NULL){
       printf("%d\t%d\t%d\n",get_nEntrega(auxMostrar), get_x(auxMostrar), get_y(auxMostrar));
        auxMostrar=next(lista);
    }
    printf("\n");
    //consulto los puntos a los cuales de los cuales quiere conseguir su distancia
    int entrega1, entrega2;
    printf("Ingrese id entrega 1: \n");
    scanf("%d", &entrega1);
    printf("ingrese id entrega 2: \n");
    scanf("%d", &entrega2);
    //recorro la lista en busca de los puntos solicitado
    coordenadas*aux=first(lista);
    while (aux!=NULL){
        if (get_nEntrega(aux)==entrega1)break;
        aux=next(lista);
    }
    coordenadas*aux2=first(lista);
    while (aux2!=NULL){
        if (get_nEntrega(aux2)==entrega2)break;
        aux2=next(lista);
    }
    //formula de distancia entre 2 puntos
    int difX = get_x(aux)-get_x(aux2);
    int difY = get_y(aux)-get_y(aux2);
    difX = pow(difX,2);
    difY = pow(difY,2);
    float distancia = sqrt( difX + difY ); 
    printf("La distancia entre la Entrega %d y la Entrega %d es: %.2f. \n",  entrega1, entrega2, distancia);
    printf("\n");
}

