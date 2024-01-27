//*****************************************************************
// File:   main.cpp
// Author: Álvaro Ramos Fustero
// Date:   mayo 2022
// Coms:   Programa de implementación de las funciones
//         definidas en el módulo betris
//*****************************************************************

#include <iostream>
using namespace std;

// CONSTANTES Y TIPOS

// Máximo múmero de filas y columnas del tablero
const int MAXDIM = 100;

// Máximo número de piezas en la entrada
const int MAXENTRADA = 3000;

// Tamaño en número de cuadrados de cada pieza
const int TAMPIEZA = 4;

// Número de piezas definidas
const int PIEZASDEF = 5;

// Códigos numéricos de colores
const int NEGRO    = 40;
const int ROJO     = 41;
const int VERDE    = 42;
const int AMARILLO = 43;
const int AZUL     = 44;
const int MAGENTA  = 45;
const int CIAN     = 46;
const int BLANCO   = 47;

// Tipo pregunta
struct pregunta{
	string frase;
	int min;
	int max;
};

//Definición preguntas existentes constantes
const pregunta pFilas = {"Introduzca número de filas y pulse enter: ", 1,MAXDIM};
const pregunta pColumnas = {"Introduzca número de columnas y pulse enter:", 1,MAXDIM};
const pregunta pRetardo = {"Introduzca el retardo deseado para mostrar los datos: ", 1,100000};


// Tipo tablero
struct tpTablero{//Ejemplo tablero:							-1-1-1-1-1
    int nfils; // Número de filas del tablero						3 3 3 4 4 -1
    int ncols; // Número de columnas del tablero					2 2 3 4 4 -1
    int matriz[MAXDIM][MAXDIM]; // El valor de cada celda indica el numero de	2 0 0 0 0 -1
               //fila  columna  // la pieza de entrada que la ocupa. 		2 0 0 0 0
                                // Si el valor es -1 entonces la casilla está vacía.
                                // Las coordenadas de la casilla de arriba a la izquierda son (0,0)
};

// Tipo pieza (color y forma)
struct tpPieza{
   int color;              // Código de color de la pieza
   int forma[TAMPIEZA][2]; // Coordenadas de los cuadrados de la pieza
                           // El primer valor es el número de fila, el segundo es el número de columna
                           // La coordenada de arriba a la izquierda es (0,0)              
     // Ejemplo de forma: [[0,0], [0,1], [1,0], [2,0] ] es la pieza  XX 
     //                                                              X 
     //                                                              X
};

// Definición de piezas existentes. El número de cada pieza es su posición en este vector
const tpPieza vPiezas[PIEZASDEF] = {		// tip forma	descripcion
    {AZUL,     {{0,0}, {0,1}, {0,2}, {0,3}}}, // 0  XXXX
    
    {VERDE,    {{0,0}, {1,0}, {2,0}, {3,0}}}, // 1  X	    x
                                              //    X	 0 1 2 3	{x,y}
                                              //    X	0
                                              //    X	1
    {ROJO,     {{0,0}, {0,1}, {1,0}, {2,0}}}, // 2  XX     y	2
                                              //    X	3
                                              //    X
    {CIAN,     {{0,0}, {0,1}, {0,2}, {1,2}}}, // 3  XXX
                                              //      X
    {AMARILLO, {{0,0}, {0,1}, {1,0}, {1,1}}}  // 4  XX
                                              //    XX
};//En dibujos son rectángulos, no cuadradis


// FUNCIONES

// Pre: −−−		(Funcion obtenida de los apuntes de programación 2, pag 30)
// Post: Presenta [pregunta] por la salida estandar (pantalla), lee la respuesta del operador
// de la entrada estandar y, si la respuesta es un entero comprendido en [min,max],
// entonces devuelve ese valor ; en caso, contrario reitera los pasos anteriores
int leerRespuesta(pregunta pregunta);

//Pre: true
//Post: mostrarVector(v, n)=mostrarVector(v, n+1)
int mostrarVector(int v[], const int n);

// Pre: true
// Post: Todas las componentes de tablero.matriz son -1 (casilla vacía)
void inicializarTablero(tpTablero &tablero);

// Pre: Tablero contiene el estado actual 
//      del tablero, en el que pueden estar colocadas algunas de dichas piezas 
// Post: Se ha mostrado el tablero por pantalla (cada pieza se ha dibujado con su color)
void mostrarTablero(const tpTablero & tablero);

// Pre: En el tablero se han colocada las n primeras piezas de vEntrada, en la columnas indicadas respectivamente en vSalida
// Post: Si las piezas colocadas completan al menos objetivo filas sin huecos,
//       entonces
//           devuelve el número de piezas colocadas, en vSalida las columnas en las que se han colocado
//           las piezas y el tablero con las piezas colocadas
//       si no devuelve -1
int buscaSolucion(tpTablero &tablero, const int vEntrada[MAXENTRADA], int vSalida[MAXENTRADA], const int objetivo, int n, const int retardo/*=0*/);

//////////////////////////////////////////////////////////////////////////////
// Salida con atributos
//
// La cadena "<ESC>[{attr1};...;{attrn}m" sirve para asignar atributos a la salida
//
// Por ejemplo: 
//    cout << "\033[34;42m" << "Hola" << "\033[0m";
// escribe en azul con fondo verde, y después resetea los atributos

// Lista de atributos estándar:
// 0 Resetea todos los atributos
// 1 brillante
// 2 tenue
// 4 subrayado
// 5 parpadeo
// 7 invertido
// 8 oculto

// Colores de primer plano
// 30 negro
// 31 rojo
// 32 verde
// 33 amarillo
// 34 azul
// 35 magenta
// 36 cian
// 37 blanco

// Colores de fondo
// 40 negro
// 41 rojo
// 42 verde
// 43 amarillo
// 44 azul
// 45 magenta
// 46 cian
// 47 blanco


