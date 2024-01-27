//*****************************************************************
// Author: Álvaro Ramos Fustero NIP:844798
// Fecha: 2022
// Descripción: Ejecutar las estrategias de Fuerza Bruta y de Divide y Vencer´as para conjuntos
// de entre 100 y 4000 intervalos generados de forma aleatoria (el valor m´ınimo para
// el extremo izquierdo del intervalo es minini y el valor m´aximo para el extremo
// derecho maxfin, ver maxsolape.hpp).
// Generar gráficas que muestren el tiempo de ejecuci´on en funci´on del n´umero de
// intervalos para cada una de las estrategias. Las gr´aficas se pueden realizar guar-
// dando las datos que se quieren mostrar en un fichero de texto y despu´es haciendo
// una llamada al sistema desde el programa.
//*****************************************************************
#include <iostream>
#include <fstream>
#include "../practica3/maxsolape.hpp"

using namespace std;


int main(){
	ofstream fich("tfb.txt");//Abro el fichero
	int maxfinint;//Entrada de parámetros
	maxfinint=maxfin;
	cout<<endl<<"Introduzca incremento en intervalos: ";
	int IncIntervalos;
	cin>>IncIntervalos;
	cout<<endl<<"Introduzca fin de intervalos: ";
	int FinIntervalos;
	cin>>FinIntervalos;
	cout<<endl<<"Introduzca 1 para DyV, y 2 para fuerza bruta: ";
	int opcion;
	cin>>opcion;
	double datos[FinIntervalos+1][2];
	tpInter vector[FinIntervalos+1];
	if (opcion==1){//DyV
		for(int i=IncIntervalos; i<=FinIntervalos; i=i+IncIntervalos){//Bucle n intervalos
			for(int j=0; j<(i-1); j++){//Generar intervalos
				vector[j].ini= rand()%maxfinint;
				vector[j].fin= rand()+vector[j].ini;
				vector[j].ind=j;
			}
			//Empiezo a contar tiempo
			clock_t t1 = clock();
			maxSolDyV(vector,0,i);
			clock_t t2 = clock();
			cout<<i<<" tarda "<< ((float(t2- t1) / CLOCKS_PER_SEC)*1000)<<"mili segundos"<<endl;
			//Acabo de contar tiempo
			//Escribo el tiempo en el archivo
			fich<<i<<" "<<((float(t2- t1) / CLOCKS_PER_SEC)*1000)<<endl;	
		}
	}
	if (opcion==2){//F Bruta
		for(int i=IncIntervalos; i<=FinIntervalos; i=i+IncIntervalos){//Bucle n intervalos
			for(int j=0; j<(i-1); j++){//Generar intervalos
				datos[j][0]= rand()%maxfinint;
				datos[j][1]= rand()+datos[j][0];;
			}
			//Empiezo a contar tiempo
			clock_t t1 = clock();
			maxSolFBruta(datos,i);
			clock_t t2 = clock();
			cout<<i<<" tarda "<< ((float(t2- t1) / CLOCKS_PER_SEC)*1000)<<"mili segundos"<<endl;
			//Acabo de contar tiempo
			//Escribo el tiempo en el archivo
			fich<<i<<"     "<<((float(t2- t1) / CLOCKS_PER_SEC)*1000)<<endl;	
		}
	}
	fich.close();
    system("gnuplot -e \"set terminal gif; set style data lines; plot 'tfb.txt'\" > tfb.gif");//Dibujamos la grafica
    return 0;

} 
