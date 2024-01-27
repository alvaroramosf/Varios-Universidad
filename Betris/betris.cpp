//*****************************************************************
// File:   betris.cpp
// Author: Álvaro Ramos Fustero
// Date:   mayo 2022
// Coms:   Programa de implementación de las funciones
//         definidas en el módulo betris
//*****************************************************************

#include <iostream>
#include "betris.hpp"

using namespace std;

//Pre: ---
//Post: Limpia el terminal (s.o. basado en unix)
void borrarPantalla(){
system("clear");
}

// Pre: −−−		(Funcion adaptada de los apuntes de programación 2, pag 30)
// Post: Presenta [pregunta] por la salida estandar (pantalla), lee la respuesta del operador
// de la entrada estandar y, si la respuesta es un entero comprendido en [min,max],
// entonces devuelve ese valor ; en caso, contrario reitera los pasos anteriores
int leerRespuesta(pregunta pregunta) {// Plantea la pregunta
cout << pregunta.frase << flush;
int respuesta;// Lee la respuesta
cin >> respuesta;
if (respuesta>=pregunta.min && respuesta<=pregunta.max) {// La respuesta es valida
	return respuesta;
}
else {// La respuesta no es valida . Desprecia el resto de la linea escrita por el operador
	const int MAXLONG = 132;
	cin.ignore(MAXLONG,'\n');// Invoca de nuevo la funcion para recabar una respuesta valida
	return leerRespuesta(pregunta);}
}

//Pre: true
//Post: mostrarVector(v, n)=mostrarVector(v, n+1)
int mostrarVector(int v[], const int n){
if (v[n]<0) return 0;
else {
cout<<" "<<v[n];
return mostrarVector(v, n+1);
}
}




// Pre: true
// Post: Todas las componentes de tablero.matriz son -1 (casilla vacía)
void inicializarTablero(tpTablero & tablero)
{
for(int fila=0; fila<tablero.nfils; fila++)
{
	for(int columna=0; columna<tablero.ncols; columna++)
	{
	tablero.matriz[fila][columna]=-1;
	}
}
}

// Pre: Tablero contiene el estado actual 
//      del tablero, en el que pueden estar colocadas algunas de dichas piezas 
// Post: Se ha borrado la info de la pantalla, y se ha mostrado el tablero por pantalla (cada pieza se ha dibujado con su color)
void mostrarTablero(const tpTablero & tablero)
{
borrarPantalla();//Borra la pantalla
for(int fila=0; fila<tablero.nfils; fila++)
{
	for(int columna=0; columna<tablero.ncols; columna++)//Ver si esto se puede implementar de otra manera
	{
	if (tablero.matriz[fila][columna]==vPiezas[0].color){
	cout << "\033[34;47m" << "\u2588";
	}
	if (tablero.matriz[fila][columna]==vPiezas[1].color){
	cout << "\033[32;47m" << "\u2588";
	}
	if (tablero.matriz[fila][columna]==vPiezas[2].color){
	cout << "\033[41;47m" << "\u2588";
	}
	if (tablero.matriz[fila][columna]==vPiezas[3].color){
	cout << "\033[36;47m" << "\u2588";
	}
	if (tablero.matriz[fila][columna]==vPiezas[4].color){
	cout << "\033[33;47m" << "\u2588";
	}
	if (tablero.matriz[fila][columna]==-1){
	cout << "\033[37;47m" << "\u2588";
	}
	}
	cout<<endl<<"\033[30;47m";
}
}

// Pre: En el tablero se han colocada las n primeras piezas de vEntrada, en la columnas indicadas respectivamente en vSalida
// Post: Si las piezas colocadas completan al menos objetivo filas sin huecos,
//       entonces
//           devuelve el número de piezas colocadas, en vSalida las columnas en las que se han colocado
//           las piezas y el tablero con las piezas colocadas
//       si no devuelve -1
int buscaSolucion(tpTablero &tablero, const int vEntrada[MAXENTRADA], int vSalida[MAXENTRADA], const int objetivo, int n, const int retardo=0)
{
return 0;
}

