//*****************************************************************
// File:   main.cpp
// Author: Álvaro Ramos Fustero
// Date:   mayo 2022
// Coms:   Programa de implementación de las funciones
//         definidas en el módulo betris
//*****************************************************************

#include <iostream>
#include "betris.hpp"

using namespace std;

struct tpTablero tablero;
int objetivo;
int retardo;
int vEntrada[MAXENTRADA];
int vSalida[MAXENTRADA];

void entradaEstandar(tpTablero& tablero, int& objetivo, int& retardo, int vEntrada[MAXENTRADA])
{
	tablero.nfils=leerRespuesta(pFilas);
	tablero.ncols=leerRespuesta(pColumnas);
	pregunta pObjetivo = {"Introduzca número de columnas que se quieren rellenar y pulse enter: ", 1, 0};
	pObjetivo.max=tablero.ncols;
	objetivo=leerRespuesta(pObjetivo);
	retardo=leerRespuesta(pRetardo);
	int nPieza=0;
	pregunta pPieza={" Introduzca la pieza deseada: ", -MAXENTRADA, PIEZASDEF};
	do{
		cout<<nPieza;
		vEntrada[nPieza]=leerRespuesta(pPieza);
		nPieza++;
	}while(vEntrada[nPieza-1]>0);
	if(vEntrada[0]<0){//Si entrada es un numero negativo, genera la secuencia aleatoriamente. MIRAR SEMILLA
	int piezasGenerar=-vEntrada[0];
	for(int i=0; i<piezasGenerar; i++){
		vEntrada[i]= rand() % PIEZASDEF;
	}
	vEntrada[piezasGenerar]=-1;
	}
}

int main(){
//Preparación
cout << "\033[30;47m";
entradaEstandar(tablero, objetivo, retardo, vEntrada);
inicializarTablero(tablero);

//Proceso
int n=0;
int piezasColocadas=buscaSolucion(tablero, vEntrada, vSalida, objetivo, n, retardo);
mostrarTablero(tablero);
//Salida final de datos
//Bucle recursivo mostrar entrada de datos
cout<<endl<<"Entrada (números de piezas):";
mostrarVector(vEntrada, 0);
//Piezas colocadas
cout<<endl<<"Numero de piezas colocadas: ";
cout<<endl<<piezasColocadas;
//Bucle recursivo mostrar salida de datos
cout<<endl<<"Salida (números de columnas):";
//mostrarVector(vSalida, 0);//El vector debe acabar en un numero negativo para parar la función, gestionar eso desde buscaSolucion
cout<<endl;
return 0;
}


