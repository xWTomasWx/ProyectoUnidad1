#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Carta
{
    char nombre[50];
    char tipo[50];
    int vida;
    int ataque;
    int defensa;
    struct Carta *siguiente;
}Carta;

void agregarEstructura(Carta **cabecera, Carta *nuevaCarta){
    if(*cabecera == NULL){
        *cabecera = nuevaCarta;
    }else{
        Carta *actual = *cabecera;
        while(actual->siguiente != NULL){
            actual = actual->siguiente;
        }
        actual->siguiente = nuevaCarta;
    }
}

void inicializarListaTexto(Carta **cabecera){
    FILE *archivo = fopen("Guardianes.txt", "r");
    if(archivo == NULL){
        printf("Error al abrir el archivo\n");
        return;
    }
    int maxLineaLongitud = 300;
    char linea[maxLineaLongitud];
    fgets(linea, maxLineaLongitud, archivo);
    while(fgets(linea, maxLineaLongitud, archivo)){
        Carta *nuevaCarta = (Carta*)malloc(sizeof(Carta));
        if(nuevaCarta == NULL){
        	printf("Error al asignar memoria para una nueva carta\n");
        	return;
		}
        strcpy(nuevaCarta->nombre, strtok(linea, ","));
        strcpy(nuevaCarta->tipo, strtok(NULL, ","));
        nuevaCarta->vida = atoi(strtok(NULL, ","));
        nuevaCarta->ataque = atoi(strtok(NULL, ","));
        nuevaCarta->defensa = atoi(strtok(NULL, ","));
        nuevaCarta->siguiente = NULL;
        agregarEstructura(cabecera, nuevaCarta);
    }
    fclose(archivo);
}



void imprimirLista(Carta *cabecera){
    Carta *actual = cabecera;
    while(actual != NULL){
        printf("Nombre: %s, Tipo: %s, Vida: %d, Ataque: %d, Defensa: %d\n", 
        actual->nombre, actual->tipo, actual->vida, actual->ataque, actual->defensa);
        actual = actual->siguiente;
    }
}

void limpiarLista(Carta *cabecera){
	while (cabecera != NULL) {
        Carta *temp = cabecera;
        cabecera = cabecera->siguiente;
        free(temp);
    }
}

int main(){
	Carta *cabecera = NULL;
    inicializarListaTexto(&cabecera);
    imprimirLista(cabecera);
	limpiarLista(cabecera);
}

