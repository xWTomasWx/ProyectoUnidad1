# The clash of the guardians

Este proyecto fue hecho para evaluar nuestra habilidad con el manejo de estructuras a través de lista enlazadas, colas o pilas. Esto a través de un juego de cartas.

## Indice
- [Datos del creador](#datos-del-creador)
- [Funcionamiento del juego](#funcionamiento-del-juego)
- [Funcionamiento del código](#funcionamiento-del-codigo)
## Datos del creador
- **Nombre**: José Peña.
- **Universidad**: Universidad de Talca.
- **Carrera**: Ingeniera en desarrollo de videojuegos y realidad virtual.
- **Modulo**: Algoritmos y estructura de datos.
- **Profesor**:Manuel Moscoso.

## Funcionamiento del juego
### Resumen del juego
En el juego cada jugador tendrá su propio mazo de 15 cartas, además tendrán carta en la mano y cartas en mesa. Cada jugador posee 5 vidas. Las cuales se perderán si es que el jugador enemigo realiza un ataque efectivo. En cada turno el jugador sacara una carta de su mazo para colocarla en su mano y deberá de escoger si atacar colocar una carta en la mesa.
### Menú principal
En este menú tenemos la posibilidad de **crear una carta**, **jugar**, **ver el historial del juego** o simplemente salir del programa.
1. **Crear carta**
Al momento de crea una carta se le solicitara el nombre de la carta y que seleccione uno de los cuatro tipos de carta que existen en el juego. Los datos como la vida, el ataque o la defensa serán dados por el programa a través de buscar los rangos máximos y mínimos de cada dato para finalmente darle un valor aleatorio entre el máximo y el mínimo.
2.  **Jugar**
Al comenzar el juego se le asignaran a cada jugador (usuario y CPU) 15 cartas del mazo inicial de manera aleatoria, en caso de que el mazo no posea 30 cartas o mas, no se podrá iniciar el juego. Cuando cada jugador posea ya su mazo de 15 cartas, cada uno deberá de seleccionar 3 cartas de dicho mazo (La CPU seleccionara de manera aleatoria). 
Cuando cada jugador halla terminado de seleccionar el juego comenzara. Primero se le mostrara un menú al usuario en el cual tiene que escoger entre **atacar**, **colocar una carta** o **mostrar cartas**.
	- **Atacar**: Si alguno de los jugadores no posee cartas en la mesa, no se podrá realizar dicha acción, pero si se posee cartas en los dos lados, entonces el jugador que vaya a atacar deberá de seleccionar una carta de su mesa para atacar a una carta enemiga, que también tendrá que ser escogida por el atacante. Si el ataque de la carta es mayor o igual a la defensa de la carta enemiga se le restara una vida al jugador enemigo, y la carta atacada será devuelta al mazo principal.
	- **Colocar carta**: Si el jugador que va a colocar una carta no posee cartas en su mano, entonces no podrá realizar esta acción, pero si posee, entonces deberá de seleccionar una carta de su mano para colocarla en la mesa.
	- **Mostrar cartas**: Esta acción permite ver que cartas posees en mano o en tu mesa.

3. **Historial**
En caso de querer volver a ver que acciones se realizaron en partida se podrá escoger la opción historial. El historial va mostrando en orden cronológico las acciones de la partida jugada. En caso de que no se haya jugado ninguna partida, no se mostrara nada.

## Funcionamiento del codigo
### Librerías usadas
Las librerías usadas son:
	- [stdio.h](https://devdocs.io/c/io)
	- [string.h](https://devdocs.io/c/string/byte)
	- [stdlib.h](https://devdocs.io/c/program)
	- [time.h](https://devdocs.io/c/chrono)

### Estructuras
Se crearon tres tipos de estructura las cuales son **jugador**, **carta**, **historial**.

1. **Jugador**: Esta estructura posee vida y tres punteros del tipo carta, que sirven para que cada jugador tenga tres listas enlazadas de las carta, una para las cartas que tienen en el mazo, otra para las cartas que poseen en mano y la ultima para las carta que tienen en mesa.
2. **Carta**: Esta estructura posee nombre, tipo, vida, ataque, defensa, un puntero del tipo carta para poder utilizarla en una lista enlazada.
3. **Historial**: Esta estructura posee la variable acción, y un puntero del tipo historial para crear una lista enlazada con esta estructura.

### Manejo de listas enlazadas
En este programa existen en total 8 listas enlazada las cuales son:

1. Lista con todas las carta: Esta lista es la que recibe las cartas del archivo, además también guarda las cartas que sean creadas por el usuario.
2. Listas de los jugadores: aquí son en total 6 listas ya que se utiliza una lista según donde se encuentra la carta de cada jugador, ya que existe una lista para el mazo de cada jugador donde se ingresan 15 cartas para comenzar el juego, estas son dos lista. Después existen otras dos las cuales representan las cartas que tiene cada jugador en su mano, estas listas reciben cartas de las listas de los mazo, o también pasan cartas a las ultimas dos listas las cuales son las carta que están en la mesa.
3. Lista del historial: Esta lista cumple la finalidad de guardar un historial de todas las acciones que se van realizando en la partida.
### Funciones
1. agregarEstructura: Esta función sirve para ingresar una estructura del tipo carta en una lista enlazada del mismo tipo.
2. quitarCartaMazo Esta función sirve para quitar una carta de una lista enlazada, pero no eliminarla, sino simplemente hacerla desaparecer de la lista, para poder ingresar esta carta en otra lista.
3. inicializarListaTexto: Esta función sirve para leer un archivo de texto que tenga los datos separados por comas, los datos que se necesitan por líneas es un nombre, un tipo, puntos de vida, puntos de ataque y puntos de defensa, para poder ser ingresados dentro de una estructura carta, y finalmente ingresar esta estructura en la lista principal.
4. rangoDefensa, rangoVida, rangoAtaque: Estas tres funciones sirven para obtener el máximo y mínimo de la vida, ataque y defensa de las cartas de una lista, para finalmente devolver un numero aleatorio en el rango del mínimo y máximo.
5. crearCarta: Esta función sirve para que el usuario cree su propia carta, a la cual le tiene que dar un nombre y escoger un tipo, los valores de vida, ataque y defensa serán dados con las funciones del punto 4, para finalmente ser ingresada en la lista principal.
6. imprimirLista: Esta función sirve para mostrar en pantalla las cartas que existen en una lista enlazada de la estructura carta.
7. limpiarLista: Esta función sirve para liberar la memoria de una lista enlazada de cartas, esto con la finalidad de que se tenga un buen manejo de la memoria utilizada.
8. verificarCantidadCartas: Esta función sirve para recorrer una lista enlazada de cartas, para que un contador se le sume uno, por cada carta que no este vacía, para finalmente devolver la cantidad de cartas que contiene la lista.
9. inicializarJugador: Esta función sirve para asignarle los puntos de vida a las estructuras de jugador, además de definir los punteros como vacíos.
10. agregarCartaMazo: Esta función sirve para para ingresar cartas en la lista del mazo de los jugadores.
11. agregarCartasMazo: Esta función sirve para ir repartiendo las cartas de la lista principal a las listas de los mazos de lo jugadores.
12. barajarMazo: Esta función sirve para revolver una lista enlazada de cartas, primero contando la cantidad de cartas que existen en la lista, para después crear un arreglo de cartas con el tamaño de la lista. Para que finalmente se vayan ingresando de la lista al arreglo, esto con la finalidad de que sea mas fácil el manejo de las carta para revolverla ya que en un arreglo es mas sencillo, después se revuelven y se ingresan en la lista.
13. obtenerCartaIndice: Esta función sirve para obtener una carta según su posición en la lista enlazada, cuando ya se tiene la carta, esta es devuelta por la función.
14. obtenerCartaDebil: Esta función sirve para buscar una carta que tenga la menor defensa en una lista, esto con la finalidad de que la CPU pueda atacar de forma mas inteligente y no de manera aleatoria.
15. juntarCartas: Esta función sirve para ingresar una lista al final de otra lista para que estas dos listas se conviertan en una sola, se pensó en esta función principalmente para que se pueda jugar mas de una vez en este programa.
16.  inicializarAccion: Esta función sirve para poder asignarle un espacio a la estructura historial, para que no existan fallos de memoria, además de asignar el siguiente en vacío.
17. juegoCartas: Esta función sirve para todo el juego aquí primero se inicializan los datos que se deban de inicializar, después se baraja el mazo principal con la función barajarMazo, para que después las carta sean repartidas a los dos jugadores, para que después los jugadores seleccionen 3 cartas de su propio mazo y moverlas a sus manos a través de la funciones quitarCartaMazo y agregarEstructura, después se barajan los dos mazos de cada jugador para que al momento de que cuando tengan que sacar una carta no sepan cual va a ser. Ahora comenzamos con los turnos los cuales para el usuario se le da un menú en donde puede atacar, colocar o ver sus cartas. Para la computadora en su turno tiene una probabilidad 4 entre 10 para colocar una carta y 6 entre 10 para atacar. Cuando alguno de los dos jugadores se quede sin vida al final de la función se libera la memoria de los jugadores, y se juntan todas las cartas para que se pueda volver a jugar sin problemas.
18. limpiarHistorial: Esta función sirve para liberar la memoria de la lista enlazada de una esructura historial.
19. imprimirHistorial: Esta función sirve para mostrar en pantalla las acciones que tiene guardadas la lista de un historial.
20. menu: Esta función sirve para que el usuario tenga un menú en el cual escoger si crear una carta, jugar, ver historia o salir.
