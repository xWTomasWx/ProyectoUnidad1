#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

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

int rangoDefensa(Carta **cabecera){
    int defensaMinima = 0, defensaMaxima = 0, defensa;
    if(*cabecera == NULL){
        printf("No hay cartas existentes\n");
        return;
    }
    Carta *actual = *cabecera;
    defensaMinima = actual->defensa;
    defensaMaxima = actual->defensa;
    actual = actual->siguiente;
    while(actual != NULL){
        if(actual->defensa < defensaMinima){
            defensaMinima = actual->defensa;
        }
        if(actual->defensa > defensaMaxima){
            defensaMaxima = actual->defensa;
        }

        actual = actual->siguiente;
    }
    defensa = rand()%(defensaMaxima-defensaMinima) + defensaMinima;
    return defensa;
}

int rangoAtaque(Carta **cabecera){
    int ataqueMinimo = 0, ataqueMaximo = 0, ataque;
    if(*cabecera == NULL){
        printf("No hay cartas existentes\n");
        return;
    }
    Carta *actual = *cabecera;
    ataqueMinimo = actual->ataque;
    ataqueMaximo = actual->ataque;
    actual = actual->siguiente;
    while(actual != NULL){
        if(actual->ataque < ataqueMinimo){
            ataqueMinimo = actual->ataque;
        }
        if(actual->ataque > ataqueMaximo){
            ataqueMaximo = actual->ataque;
        }

        actual = actual->siguiente;
    }
    ataque = rand()%(ataqueMaximo-ataqueMinimo) + ataqueMinimo;
    return ataque;
}

int rangoVida(Carta **cabecera){
    int vidaMinima = 0, vidaMaxima = 0, vida;
    if(*cabecera == NULL){
        printf("No hay cartas existentes\n");
        return;
    }
    Carta *actual = *cabecera;
    vidaMinima = actual->vida;
    vidaMaxima = actual->vida;
    actual = actual->siguiente;
    while(actual != NULL){
        if(actual->vida < vidaMinima){
            vidaMinima = actual->vida;
        }
        if(actual->vida > vidaMaxima){
            vidaMaxima = actual->vida;
        }

        actual = actual->siguiente;
    }
    vida = rand()%(vidaMaxima-vidaMinima) + vidaMinima;
    return vida;
}

void crearCarta(Carta **cabecera){
    if(*cabecera == NULL){
        printf("No hay cartas existentes\n");
        return;
    }
    Carta *nuevaCarta = (Carta*)malloc(sizeof(Carta));
    if(nuevaCarta == NULL){
        printf("Error al asignar memoria para una nueva carta\n");
        return;
	}
    int opcion = 0;
    printf("\nIngrese el nombre de la carta: ");
    scanf("%s", &nuevaCarta->nombre);
    
    while(opcion > 4 || opcion < 1){
        printf("Seleccione un tipo para su carta:\n1) Mago\n2) Vikingo\n3) Nigromante\n4) Bestia\n");
        printf("Ingrese el numero: ");
        scanf("%d", &opcion);
        if(opcion == 1){
            strcpy(nuevaCarta->tipo, "Mage");
        }
        if(opcion == 2){
            strcpy(nuevaCarta->tipo, "Viking");
        }
        if(opcion == 3){
            strcpy(nuevaCarta->tipo, "Necromancer");
        }
        if(opcion == 4){
            strcpy(nuevaCarta->tipo, "Beast");
        }
        if(opcion > 4 || opcion < 1){
            printf("Opcion no valida\n");
        }
    }
    
    nuevaCarta->vida = rangoVida(cabecera);
    nuevaCarta->ataque = rangoAtaque(cabecera);
    nuevaCarta->defensa = rangoDefensa(cabecera);
    agregarEstructura(cabecera, nuevaCarta);
    printf("\nCarta creada con exito\n");
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
        Carta *temporal = cabecera;
        cabecera = cabecera->siguiente;
        free(temporal);
    }
}

void menu(Carta **cabecera){
    int opcion=0;
    while(opcion != 4){
        printf("Seleccione una opcion:\n1) Crear carta\n2) Jugar\n3) Ver historial\n4) Salir\n");
        printf("Ingrese el numero: ");
        scanf("%d", &opcion);
        if(opcion == 1){
            crearCarta(cabecera);
        }
        if(opcion == 2){
            
        }
        if(opcion == 3){
            
        }
        if(opcion == 4){
            printf("Saliendo del juego\n");
        }
        if(opcion < 1 || opcion > 4){
            printf("Opcion no valida\n");
        }
        
    }
}

int main(){
    srand(time(NULL));
	Carta *cabecera = NULL;
    inicializarListaTexto(&cabecera);
    menu(&cabecera);
    imprimirLista(cabecera);
	limpiarLista(cabecera);
	
	return 0;
}

