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

typedef struct 
{
    int vida;
    Carta *cabeceraCartasEnMano;
    Carta *cabeceraCartasEnMesa;
    Carta *cabeceraCartasEnMazo;
}Jugador;


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
        exit(-1);
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
        if(scanf("%d", &opcion) != 1){
        	opcion = 5;
        	while(getchar() != '\n');
		}
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
    int contador = 1;
    while(actual != NULL){
        printf("%d) Nombre: %s, Tipo: %s, Vida: %d, Ataque: %d, Defensa: %d\n", contador,
        actual->nombre, actual->tipo, actual->vida, actual->ataque, actual->defensa);
        actual = actual->siguiente;
        contador++;
    }
}

void limpiarLista(Carta *cabecera){
	while (cabecera != NULL) {
        Carta *temporal = cabecera;
        cabecera = cabecera->siguiente;
        free(temporal);
    }
}

int verificarCantidadCartas(Carta **cabecera){
    Carta *actual = *cabecera;
    int contador = 0;
    while(actual != NULL){
        contador++;
        actual = actual->siguiente;
    }
    if(contador >= 30){
        return 1;
    }else{
        return 0;
    }
}

void inicializarJugador(Jugador *jugador){
    jugador->vida = 5;
    jugador->cabeceraCartasEnMano = NULL;
    jugador->cabeceraCartasEnMazo = NULL;
    jugador->cabeceraCartasEnMesa = NULL;
}

void agregarCartaMazo(Jugador *jugador, Carta *carta){
    if(jugador->cabeceraCartasEnMazo == NULL){
        jugador->cabeceraCartasEnMazo = carta;
        return;
    }
    Carta *actual = jugador->cabeceraCartasEnMazo;
    while(actual->siguiente != NULL){
        actual = actual->siguiente;
    }
    actual->siguiente = carta;
}

void agregarCartasMazo(Jugador *usuario, Jugador *CPU, Carta **cabecera){
    
    
    int i;
    for(i=0; i<15; i++){
    	Carta *actual = *cabecera;
    	Carta *anterior = actual;
        while(actual->siguiente != NULL){
        	anterior = actual;
        	actual = actual->siguiente;
		}
		anterior->siguiente = actual->siguiente;
		actual->siguiente = NULL;
		agregarCartaMazo(usuario, actual);
		Carta *actual2 = *cabecera;
    	Carta *anterior2 = actual2;
        while(actual2->siguiente != NULL){
        	anterior2 = actual2;
        	actual2 = actual2->siguiente;
		}
		anterior2->siguiente = actual2->siguiente;
		actual2->siguiente = NULL;
		agregarCartaMazo(CPU, actual2);
    }
}

void barajarMazo(Carta **cabecera) {
    int cantidadCartas = 0;
    Carta *actual = *cabecera;
    while (actual != NULL) {
        cantidadCartas++;
        actual = actual->siguiente;
    }

    Carta *cartas[cantidadCartas];
    actual = *cabecera;
    int i = 0;
    while (actual != NULL) {
        cartas[i] = actual;
        actual = actual->siguiente;
        i++;
    }

    for (i = cantidadCartas - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Carta *temp = cartas[i];
        cartas[i] = cartas[j];
        cartas[j] = temp;
    }

    *cabecera = cartas[0];
    for (i = 0; i < cantidadCartas - 1; i++) {
        cartas[i]->siguiente = cartas[i + 1];
    }
    cartas[cantidadCartas - 1]->siguiente = NULL;
}

void juegoCartas(Carta **cabecera){
    if(verificarCantidadCartas(cabecera) == 0){
        printf("\nNumero de cartas insuficientes para comenzar a jugar\n");
        return;
    }
    
    Jugador *usuario = (Jugador*)malloc(sizeof(Jugador));
    Jugador *CPU = (Jugador*)malloc(sizeof(Jugador));
    inicializarJugador(usuario);
    inicializarJugador(CPU);
    
    barajarMazo(cabecera);
	
    agregarCartasMazo(usuario, CPU, cabecera);
    
    
    imprimirLista(usuario->cabeceraCartasEnMazo);
    printf("\n\n\n");
    imprimirLista(CPU->cabeceraCartasEnMazo);
	printf("\n\n\n");
    imprimirLista(*cabecera);
	
	
	limpiarLista(usuario->cabeceraCartasEnMano);
	limpiarLista(usuario->cabeceraCartasEnMazo);
	limpiarLista(usuario->cabeceraCartasEnMesa);
	limpiarLista(CPU->cabeceraCartasEnMano);
	limpiarLista(CPU->cabeceraCartasEnMazo);
	limpiarLista(CPU->cabeceraCartasEnMesa);
}

void menu(Carta **cabecera){
    int opcion=0;
    while(opcion != 4){
        printf("Seleccione una opcion:\n1) Crear carta\n2) Jugar\n3) Ver historial\n4) Salir\n");
        printf("Ingrese el numero: ");
        if(scanf("%d", &opcion) != 1){
        	opcion = 5;
        	while(getchar() != '\n');
		}
        if(opcion == 1){
            crearCarta(cabecera);
        }
        if(opcion == 2){
            juegoCartas(cabecera);
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

