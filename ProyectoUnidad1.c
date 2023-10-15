#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
//Estructura donde se guardan los datos de la carta
typedef struct Carta
{
    char nombre[50];
    char tipo[50];
    int vida;
    int ataque;
    int defensa;
    struct Carta *siguiente;
}Carta;
//Estructura para los jugadores que poseen distintas listas segun donde esten las cartas
typedef struct 
{
    int vida;
    Carta *cabeceraCartasEnMano;
    Carta *cabeceraCartasEnMesa;
    Carta *cabeceraCartasEnMazo;
}Jugador;
//Estructura donde se guardan los datos de cada accion realizada en el juego
typedef struct Historial{
    char accion[500];
    struct Historial *siguiente;
}Historial;

//Esta funcion sirve para agregar una estructura carta en una lista enlazada
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
//Esta funcion sirve para quitar una estructura carta de una lista enlazada para ser utilizada en otra lista (no elimina la estructura)
void quitarCartaMazo(Carta **cabecera, Carta *carta){   
    Carta *actual = *cabecera;
    Carta *anterior = NULL;

    while(actual != NULL){
        if(actual == carta){
            if(anterior != NULL){
                anterior->siguiente = actual->siguiente;
            }else{
                *cabecera = actual->siguiente;
            }
            carta->siguiente = NULL;
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
}
//Esta funcion sirve para ingresar datos a las estructuras cartas a travez de un texto con la finalidad de crear una lista enlazada con esto
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
        	exit(-1);
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
//Esta funcion sirve para verificar la defensa que puede tener una carta creada por el usuario
int rangoDefensa(Carta **cabecera){
    int defensaMinima = 0, defensaMaxima = 0, defensa;
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
//Esta funcion sirve para verificar el ataque que puede tener una carta creada por el usuario
int rangoAtaque(Carta **cabecera){
    int ataqueMinimo = 0, ataqueMaximo = 0, ataque;
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
//Esta funcion sirve para verificar la vida que puede tener una carta creada por el usuario
int rangoVida(Carta **cabecera){
    int vidaMinima = 0, vidaMaxima = 0, vida;
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
//Esta funcion sirve para  crear una carta a travez del usuario
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
    scanf("%49s", nuevaCarta->nombre);
    
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
//Esta funcion sirve para imprimir toda la lista enlazada de estructuras de cartas con un indice al principio
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
//Esta funcion sirve para limpiar las listas (liberar memoria)
void limpiarLista(Carta *cabecera){
	while (cabecera != NULL) {
        Carta *temporal = cabecera;
        cabecera = cabecera->siguiente;
        free(temporal);
    }
}
//Esta funcion sirve para devolver el numero de estructuras cartas que posee la lista enlazada
int verificarCantidadCartas(Carta **cabecera){
    Carta *actual = *cabecera;
    int contador = 0;
    while(actual != NULL){
        contador++;
        actual = actual->siguiente;
    }
    return contador;
}
//Esta funcion sirve para darle valores a las variables de las estructuras jugador
void inicializarJugador(Jugador *jugador){
    jugador->vida = 5;
    jugador->cabeceraCartasEnMano = NULL;
    jugador->cabeceraCartasEnMazo = NULL;
    jugador->cabeceraCartasEnMesa = NULL;
}
//Esta funcion sirve para ingresar una estructura carta en la lista del mazo del jugador
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
//Esta funcion sirve para darles 15 cartas a cada jugador
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
//Esta funcion sirve para mezclar una lista de cartas
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
//Esta funcion sirve para obtener una carta segun su posicion en la lista enlazada
Carta *obtenerCartaIndice(Carta **cabecera, int contador){
    int i;
    Carta *actual = *cabecera;
    for(i=1; i<contador; i++){
        actual = actual->siguiente;
    }
    return actual;
}
//Esta funcion sirve para obtener una carta segun su defensa, devuelve la carta con menor defensa
Carta *obtenerCartaDebil(Carta **cabecera){
    Carta *actual = *cabecera;
    Carta *cartaDebil = actual;
    while(actual != NULL){
        if(actual->defensa < cartaDebil->defensa){
            cartaDebil = actual;
        }
        actual = actual->siguiente;
    }
    return cartaDebil;
}
//Esta funcion sirve para juntar dos lista de cartas, esto con la finalidad de volver a tener el mazo inicial completo
void juntarCartas(Carta **cabeceraPrincipal, Carta **cabeceraSecundaria){
	Carta *actual = *cabeceraPrincipal;
	if(actual == NULL){
		cabeceraPrincipal = cabeceraSecundaria;
	}
	while(actual->siguiente != NULL){
		actual = actual->siguiente;
	}
	actual->siguiente = *cabeceraSecundaria;
}
//Esta funcion sirve para asignarle espacio a la estructura historial y colocar el siguiente en null
Historial *inicializarAccion(){
    Historial *accionH = (Historial*)malloc(sizeof(Historial));
    accionH->siguiente = NULL;
    return accionH;
}

//Esta funcion sirve para correr todo el juego de cartas (quizas tuve que crear mas funciones, esta funcion quedo muy larga)
void juegoCartas(Carta **cabecera, Historial **historial){
    if(verificarCantidadCartas(cabecera) < 30){
        printf("\nNumero de cartas insuficientes para comenzar a jugar\n");
        return;
    }
    Historial *accionH = inicializarAccion();
    
    Jugador *usuario = (Jugador*)malloc(sizeof(Jugador));
    Jugador *CPU = (Jugador*)malloc(sizeof(Jugador));
    inicializarJugador(usuario);
    inicializarJugador(CPU);
    
    barajarMazo(cabecera);
	
    agregarCartasMazo(usuario, CPU, cabecera);
    
    strcpy(accionH->accion, "Los jugadores escogeran cartas para su mano");
    *historial = accionH;
    Historial *actualH = *historial;
    int contador = 0, opcion;
    while(contador < 3){
        printf("Seleccione una carta para su mano:\n");
        imprimirLista(usuario->cabeceraCartasEnMazo);
        printf("Ingrese el numero: ");
        if(scanf("%d", &opcion) != 1){
        	opcion = verificarCantidadCartas(&usuario->cabeceraCartasEnMazo)+1;
        	while(getchar() != '\n');
		}
        if(opcion > 0 && opcion < (verificarCantidadCartas(&usuario->cabeceraCartasEnMazo)+1)){
            Carta *cartaElegida = obtenerCartaIndice(&usuario->cabeceraCartasEnMazo, opcion);
            quitarCartaMazo(&usuario->cabeceraCartasEnMazo, cartaElegida);
            agregarEstructura(&usuario->cabeceraCartasEnMano, cartaElegida);
            contador++;
            accionH = inicializarAccion();
            strcpy(accionH->accion, "El usuario selecciono la carta ");
            strcat(accionH->accion, cartaElegida->nombre);
            actualH->siguiente = accionH;
			actualH = actualH->siguiente;
            
            Carta *cartaRandom = obtenerCartaIndice(&CPU->cabeceraCartasEnMazo, rand()%verificarCantidadCartas(&CPU->cabeceraCartasEnMazo)+1);
            quitarCartaMazo(&CPU->cabeceraCartasEnMazo, cartaRandom);
            agregarEstructura(&CPU->cabeceraCartasEnMano, cartaRandom);
            accionH = inicializarAccion();
            strcpy(accionH->accion, "La CPU selecciono la carta ");
            strcat(accionH->accion, cartaRandom->nombre);
            actualH->siguiente = accionH;
			actualH = actualH->siguiente;
            
        }else{
            printf("Opcion no valida\n");
        }
    }
    
    barajarMazo(&usuario->cabeceraCartasEnMazo);
    
    opcion = 0;
    int activarTurnoCPU = 0, sacarCarta = 0;
    while(usuario->vida > 0 && CPU->vida > 0){
    	if(opcion != 3 && sacarCarta == 0){
    		if(verificarCantidadCartas(&usuario->cabeceraCartasEnMazo) > 0){
	            Carta *carta = obtenerCartaIndice(&usuario->cabeceraCartasEnMazo, 1);
	            quitarCartaMazo(&usuario->cabeceraCartasEnMazo, carta);
	            agregarEstructura(&usuario->cabeceraCartasEnMano, carta);
	            printf("Carta obtenida:\nNombre: %s, Tipo: %s, Vida: %d, Ataque: %d, Defensa: %d\n", 
	                    carta->nombre, carta->tipo, carta->vida, carta->ataque, carta->defensa);
                
                accionH = inicializarAccion();
                strcpy(accionH->accion, "El usuario saco del mazo la carta ");
                strcat(accionH->accion, carta->nombre);
                actualH->siguiente = accionH;
				actualH = actualH->siguiente;
	        }else{
	            printf("No quedan cartas en tu mazo\n");
	        }
		}
    	
    	printf("Seleccione una opcion:\n1) Atacar\n2) Colocar carta\n3) Mostrar cartas (no gasta tu turno)\n");
        printf("Ingrese el numero: ");
        if(scanf("%d", &opcion) != 1){
        	opcion = 4;
        	while(getchar() != '\n');
		}
        activarTurnoCPU = 1;
        
        if(opcion == 1){
            if(verificarCantidadCartas(&usuario->cabeceraCartasEnMesa) > 0){
                if(verificarCantidadCartas(&CPU->cabeceraCartasEnMesa) > 0){
                    int opcion4, verificar = 0;
                    while(verificar == 0){
                        printf("Seleccione una carta para atacar:\n");
                        imprimirLista(usuario->cabeceraCartasEnMesa);
                        printf("Ingrese el numero: ");
                        if(scanf("%d", &opcion4) != 1){
                            opcion4 = verificarCantidadCartas(&usuario->cabeceraCartasEnMesa)+1;
                            while(getchar() != '\n');
                        }
                        if(opcion4 > 0 && opcion4 < (verificarCantidadCartas(&usuario->cabeceraCartasEnMesa)+1)){
                            Carta *cartaElegida = obtenerCartaIndice(&usuario->cabeceraCartasEnMesa, opcion4);
                            int opcion5 = 0;
                            printf("Seleccione la carta enemiga que va a atacar:\n");
                            imprimirLista(CPU->cabeceraCartasEnMesa);
                            printf("Ingrese el numero: ");
                            if(scanf("%d", &opcion5) != 1){
                                opcion4 = verificarCantidadCartas(&CPU->cabeceraCartasEnMesa)+1;
                                while(getchar() != '\n');
                            }
                            if(opcion5 > 0 && opcion5 < (verificarCantidadCartas(&CPU->cabeceraCartasEnMesa+1))){
                                Carta *cartaEnemiga = obtenerCartaIndice(&CPU->cabeceraCartasEnMesa, opcion5);

                                accionH = inicializarAccion();
                                strcpy(accionH->accion, "El usuario ataco con la carta ");
                                strcat(accionH->accion, cartaElegida->nombre);
                                actualH->siguiente = accionH;
			                    actualH = actualH->siguiente;

                                accionH = inicializarAccion();
                                strcpy(accionH->accion, "El ataque lo recibio la carta ");
                                strcat(accionH->accion, cartaEnemiga->nombre);
                                    

                                if(cartaElegida->ataque >= cartaEnemiga->defensa){
                                    CPU->vida--;
                                    quitarCartaMazo(&CPU->cabeceraCartasEnMesa, cartaEnemiga);
                                    juntarCartas(cabecera, &cartaEnemiga);

                                    strcat(accionH->accion, ", el ataque funciono, la CPU perdio 1 de vida");

                                    printf("El enemigo perdio un punto de vida, le quedan %d\n", CPU->vida);
                                    if(CPU->vida <= 0){
                                        strcat(accionH->accion, ", GANO EL USUARIO");
                                        activarTurnoCPU = 0;
                                        printf("\nFELICIDADES GANASTE LA PARTIDA\n");
                                    }
                                }else{
                                    strcat(accionH->accion, ", el ataque fallo");
                                    printf("Tu ataque fallo\n");
                                }
                                actualH->siguiente = accionH;
			                    actualH = actualH->siguiente;
                                verificar = 1;
                                sacarCarta = 0;
                            }else{
                                printf("Opcion no valida\n");
                            }

                        }else{
                            printf("Opcion no valida\n");
                        }
                    }
                }else{
                    printf("El enemigo no posee cartas en mesa\n");
                    activarTurnoCPU = 0;
                    sacarCarta = 1;
                }
            }else{
                printf("No posees cartas en la mesa, intente colocar una para comenzar a atacar\n");
                activarTurnoCPU = 0;
                sacarCarta = 1;
            }
        }
        if(opcion == 2){
        	if(verificarCantidadCartas(&usuario->cabeceraCartasEnMano) > 0){
                int opcion2, verificar = 0;
                while(verificar == 0){
                    printf("Seleccione una carta para colocar en la mesa:\n");
                    imprimirLista(usuario->cabeceraCartasEnMano);
                    printf("Ingrese el numero: ");
                    if(scanf("%d", &opcion2) != 1){
                        opcion2 = verificarCantidadCartas(&usuario->cabeceraCartasEnMano)+1;
                        while(getchar() != '\n');
                    }
                    if(opcion2 > 0 && opcion2 < (verificarCantidadCartas(&usuario->cabeceraCartasEnMano)+1)){
                        Carta *cartaElegida = obtenerCartaIndice(&usuario->cabeceraCartasEnMano, opcion2);
                        quitarCartaMazo(&usuario->cabeceraCartasEnMano, cartaElegida);
                        agregarEstructura(&usuario->cabeceraCartasEnMesa, cartaElegida);
                        verificar = 1;
                        sacarCarta = 0;
                        accionH = inicializarAccion();
                        strcpy(accionH->accion, "El usuario coloco la carta ");
                        strcat(accionH->accion, cartaElegida->nombre);
                        actualH->siguiente = accionH;
			            actualH = actualH->siguiente;
                        printf("\nCarta colocada\n");
                    }else{
                        printf("Opcion no valida\n");
                    }
                }
            }else{
                printf("No hay suficientes cartas en la mano para colocar\n");
                activarTurnoCPU = 0;
                sacarCarta = 1;
            }
        }
        if(opcion == 3){
            int opcion3 = 0;
            while(opcion3 < 1 || opcion3 > 2){
                printf("Seleccione una opcion:\n1) Ver cartas de la mano\n2) Ver cartas de la mesa\n");
                printf("Ingrese el numero: ");
                if(scanf("%d", &opcion3) != 1){
                    opcion3 = 3;
                    while(getchar() != '\n');
                }
                if(opcion3 == 1){
                    imprimirLista(usuario->cabeceraCartasEnMano);
                }
                if(opcion3 == 2){
                    imprimirLista(usuario->cabeceraCartasEnMesa);
                }
                if(opcion3 == 3){
                    printf("Opcion no valida\n");
                }
            }
            activarTurnoCPU = 0;
        }
        if(opcion < 1 || opcion > 3){
        	printf("Opcion no valida\n");
        	sacarCarta = 1;
        	activarTurnoCPU = 0;
		}

        if(activarTurnoCPU == 1){
            int accionRandom;
            if(verificarCantidadCartas(&CPU->cabeceraCartasEnMazo) > 0){
                Carta *carta = obtenerCartaIndice(&CPU->cabeceraCartasEnMazo, 1);
                quitarCartaMazo(&CPU->cabeceraCartasEnMazo, carta);
                agregarEstructura(&CPU->cabeceraCartasEnMano, carta);

                accionH = inicializarAccion();
                strcpy(accionH->accion, "La CPU saco del mazo la carta ");
                strcat(accionH->accion, carta->nombre);
                actualH->siguiente = accionH;
			    actualH = actualH->siguiente;

                printf("CPU Obtuvo una carta\n");
            }else{
                printf("No quedan cartas en el mazo de CPU\n");
            }
            int turnoCPU = 0, activar1 = 0, activar2 = 0;
            while(turnoCPU == 0 && (activar1 == 0 || activar2 == 0)){
                turnoCPU = 1;
                accionRandom = rand()%10+1;
                if(accionRandom < 4){
                    if(verificarCantidadCartas(&CPU->cabeceraCartasEnMano) > 0){
                        Carta *cartaElegida = obtenerCartaIndice(&CPU->cabeceraCartasEnMano, rand()%verificarCantidadCartas(&CPU->cabeceraCartasEnMano)+1);
                        quitarCartaMazo(&CPU->cabeceraCartasEnMano, cartaElegida);
                        agregarEstructura(&CPU->cabeceraCartasEnMesa, cartaElegida);
                        printf("CPU coloco la carta:\nNombre: %s, Tipo: %s, Vida: %d, Ataque: %d, Defensa: %d\n",
                                cartaElegida->nombre, cartaElegida->tipo, cartaElegida->vida, cartaElegida->ataque, cartaElegida->defensa);

                        accionH = inicializarAccion();
                        strcpy(accionH->accion, "La CPU coloco la carta ");
                        strcat(accionH->accion, cartaElegida->nombre);
                        actualH->siguiente = accionH;
			            actualH = actualH->siguiente;

                    }else{
                        turnoCPU = 0;
                        activar1 = 1;
                    }
                }else{
                    if(verificarCantidadCartas(&CPU->cabeceraCartasEnMesa) > 0){
                        if(verificarCantidadCartas(&usuario->cabeceraCartasEnMesa) > 0){
                            Carta *cartaRandom = obtenerCartaIndice(&CPU->cabeceraCartasEnMesa, rand()%verificarCantidadCartas(&CPU->cabeceraCartasEnMesa)+1);
                            Carta *cartaDebil = obtenerCartaDebil(&usuario->cabeceraCartasEnMesa);
                            printf("La carta enemiga %s ataco a tu carta %s\n", cartaRandom->nombre, cartaDebil->nombre);

                            accionH = inicializarAccion();
                            strcpy(accionH->accion, "La CPU ataco con la carta ");
                            strcat(accionH->accion, cartaRandom->nombre);
                            actualH->siguiente = accionH;
			                actualH = actualH->siguiente;

                            accionH = inicializarAccion();
                            strcpy(accionH->accion, "El ataque lo recibio la carta ");
                            strcat(accionH->accion, cartaDebil->nombre);

                            if(cartaRandom->ataque >= cartaDebil->defensa){
                                usuario->vida--;
                                quitarCartaMazo(&usuario->cabeceraCartasEnMesa, cartaDebil);
                                juntarCartas(cabecera, &cartaDebil);
                                strcat(accionH->accion, ", el ataque funcion, el usuario perdio 1 vida");
                                printf("El enemigo te ataco perdiste un punto de vida, te quedan %d\n", usuario->vida);
                                if(usuario->vida <= 0){
                                    strcat(accionH->accion, ", GANO LA CPU");
                                    printf("LA CPU GANO LA PARTIDA\n");
                                }
                            }else{
                                strcat(accionH->accion, ", el ataque fallo");
                                printf("El ataque fallo\n");
                            }
                            actualH->siguiente = accionH;
			                actualH = actualH->siguiente;
                        }else{
                            turnoCPU = 0;
                            contador++;
                            activar2 = 1;
                        }
                    }else{
                        turnoCPU = 0;
                        contador++;
                        activar2 = 1;
                    }
                }
            }
        }
	}
    //Aqui junto todas las carta para cuando termine el programa en la funcion limpiar lista se liberen todas las cartas a la vez
    //tambien sirve para que vuelvan a jugar ya que con esto estaria todo el mazo ya listo
	juntarCartas(cabecera, &usuario->cabeceraCartasEnMano);
	juntarCartas(cabecera, &usuario->cabeceraCartasEnMazo);
	juntarCartas(cabecera, &usuario->cabeceraCartasEnMesa);
	juntarCartas(cabecera, &CPU->cabeceraCartasEnMano);
	juntarCartas(cabecera, &CPU->cabeceraCartasEnMazo);
	juntarCartas(cabecera, &CPU->cabeceraCartasEnMesa);
	free(usuario);
	free(CPU);
}
//Esta funcion sirve para liberar la memoria que utiliza el historial
void limpiarHistorial(Historial *historial){
    while (historial != NULL) {
        Historial *temporal = historial;
        historial = historial->siguiente;
        free(temporal);
    }
}
//Imprime las acciones de una lista de estructura historial
void imprimirHistorial(Historial *historial){
    Historial *actual = historial;
    if(actual == NULL){
        printf("Todavia no se inicia una partida\n");
        return;
    }
    while(actual != NULL){
        printf("%s\n", actual->accion);
        actual = actual->siguiente;
    }
}

//Esta funcion sirve para el menu principal, ofrece crear carta, jugar o mostrar el historial
void menu(Carta **cabecera){
    int opcion=0;
    Historial *historial = NULL;
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
            limpiarHistorial(historial);
            historial = NULL;
            juegoCartas(cabecera, &historial);
        }
        if(opcion == 3){
            imprimirHistorial(historial);
        }
        if(opcion == 4){
            printf("Saliendo del juego\n");
            limpiarHistorial(historial);
            return;
        }
        if(opcion < 1 || opcion > 4){
            printf("Opcion no valida\n");
        }
        
    }
}
//La funcion principal donde inicia todo
int main(){
    srand(time(NULL));
	Carta *cabecera = NULL;
    inicializarListaTexto(&cabecera);
    menu(&cabecera);
	limpiarLista(cabecera);
	
	return 0;
}

