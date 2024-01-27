//*****************************************************************
// Author: Álvaro Ramos Fustero NIP:844798
//*****************************************************************
#include "maxsolape.hpp"

/*ESTRUCTURAS DE DATOS DE REFERENCIA
struct tpSolape{
    int interA, interB; 	Indice de los intervalos en la matriz
    double solape;      	Solape de los intervalos
};

struct tpInter{
    int ind;            	Indice del intervalo en la matriz inicial
    double ini, fin;  		Inicio y fin del intervalo
};
*/



//Funcion intercambiar tpInter
void movInter(tpInter destino, tpInter origen){
	destino.ind=origen.ind;
	destino.ini=origen.ini;
	destino.fin=origen.fin;
	return;
}

//Funcion intercambiar tpSolape
void movSolape(tpSolape destino, tpSolape origen){
	destino.interA=origen.interA;
	destino.interB=origen.interB;
	destino.solape=origen.solape;
	return;
}


//Solape entre dos intervalos
double solapeInter(tpInter a, tpInter b){
	double min, max;
	if(a.ini>b.ini) max=a.ini;
	else max=b.ini;
	if(a.fin<b.fin) min=a.fin;
	else min=b.fin;
	return min-max;
}
// Crea un vector de tpInter con los n primeros intervalos de inters.
// Por ejemplo para la matrix inters de la funcion anterior y n=5, los
// valores de indinters seran:
// [{ind: 0, ini: 1.5, fin: 8.0},
//  {ind: 1, ini: 0.0, fin: 4.5},
//  {ind: 2, ini: 2.0, fin: 4.0},
//  {ind: 3, ini: 1.0, fin: 6.0},
//  {ind: 4, ini: 3.5, fin: 7.0}]
void crearvind(double inters[N][2], tpInter indinters[N], int n){
	for(int i=0; i<n; i++){
		indinters[i].ind=i;
		indinters[i].ini=inters[i][0];
		indinters[i].fin=inters[i][1];
	}
}

//Funcion aux merge
void merge(tpInter v[N], int p, int m, int f){
	tpInter b[f+1];
	int h=p;
	int i=p;
	int j=m+1;
	while(h<=m && j<=f){
		if(v[h].ini <= v[j].ini){
			b[i].ind=v[h].ind;
			b[i].ini=v[h].ini;
			b[i].fin=v[h].fin;
			h=h+1;
		}
		else{
			b[i].ind=v[j].ind;
			b[i].ini=v[j].ini;
			b[i].fin=v[j].fin;
			j=j+1;
		}
		i=i+1;
	}
	if (h>m){
		for (int k=j; k<=f; k++){
			b[i].ind=v[k].ind;
			b[i].ini=v[k].ini;
			b[i].fin=v[k].fin;
			i=i+1;
		}
	}
	else{
		for (int k=h; k<=m; k++){
			b[i].ind=v[k].ind;
			b[i].ini=v[k].ini;
			b[i].fin=v[k].fin;
			i=i+1;
		}
	}
	for(int k=p; k<=f; k++){
		v[k].ind=b[k].ind;
		v[k].ini=b[k].ini;
		v[k].fin=b[k].fin;
	}
}

// Ordena con el algoritmo mergesort los intervalos de indinters
// comprendidos entre las componentes indexadas por p y f, ambas incluidas,
// de acuerdo al valor de inicio de los intervalos (orden creciente).
// Por ejemplo, para el vector de la funcion anterior, p=0 y f=4, el vector
// ordenado sera:
// [{ind: 1, ini: 0.0, fin: 4.5},
//  {ind: 3, ini: 1.0, fin: 6.0},
//  {ind: 0, ini: 1.5, fin: 8.0},
//  {ind: 2, ini: 2.0, fin: 4.0},
//  {ind: 4, ini: 3.5, fin: 7.0}]
void mergesortIndInters(tpInter indinters[N], int p, int f){
	if(p<f){
	int medio=(p+f)/2;
	mergesortIndInters(indinters, p, medio);
	mergesortIndInters(indinters, medio+1, f);
	merge(indinters, p, medio, f);//Combinar soluciones
	}
}

// maxSolFBruta devuelve un registro tpSolape en el que el campo solape
// es el maximo solape entre parejas de los n primeros intervalos de inters,
// y los campos interA e interB son los indices de dichos intervalos.
// Para la matriz inters de ejemplo, el resultado es solape=4.5, interA=0,
// interB=3
// (los valores de interA e interB pueden estar intercambiados, es decir,
// el resultado para el ejemplo anterior tambi�n puede ser solape=4.5,
// interA=3, interB=0).
tpSolape maxSolFBruta(double inters[N][2], int n){
	double min, max;
	tpSolape solucion;
	solucion.solape=0;
	for(int i=0; i<n; i++){
		for(int j=(i+1); j<n; j++){
			if(inters[i][0]>inters[j][0]) max=inters[i][0];
			else max=inters[j][0];
			if(inters[i][1]<inters[j][1]) min=inters[i][1];
			else min=inters[j][1];
			if(min-max>solucion.solape){
				solucion.solape=min-max;
				solucion.interA=i;
				solucion.interB=j;
			}
		}		
	}
	return solucion;
}

//Funcion auxiliar de DyV
tpSolape auxMaxSolDyV (tpInter indinters[N],int p,int f){
	int medio=(p+f)/2;
	int maxFin=p;
	int indiceSegParte=medio+1;
	tpSolape solape,solucion;
	double maxSolape=0.0;
	for(int j=p;j<medio+1;j++){
		if(indinters[j].fin>indinters[maxFin].fin){
			maxFin=j;
		}
	}
	for(int i=medio+1;i<f+1;i++){
		solape.solape=solapeInter(indinters[maxFin],indinters[i]);
		if(solape.solape>maxSolape){
			maxSolape=solape.solape;
			indiceSegParte=i;
		}
	}
	solucion.interA=indinters[maxFin].ind;
	solucion.interB=indinters[indiceSegParte].ind;
	solucion.solape=maxSolape;
	return solucion;
}

// Dado un vector indinters, utiliza la tecnica de Divide y Venceras para
// devolver el maximo solape entre parejas de intervalos comprendidos
// entre las componentes indexadas por p y f, ambas incluidas.
// Por ejemplo, para el vector del procedimiento anterior,
// el resultado es solape=4.5, interA=0, interB=3
tpSolape maxSolDyV(tpInter indinters[N], int p, int f){
	tpSolape solape,mitadMenor,mitadMayor,fusion;
	mergesortIndInters(indinters,p,f);
	int medio=(p+f)/2;
	if(p-f==0){//Casos base
		solape.interA=indinters[p].ind;
		solape.interB=indinters[f].ind;
		solape.solape=0;
		return solape;	
	}
	else{//Casos recursivos
		mitadMenor=maxSolDyV(indinters,p,medio);
		mitadMayor=maxSolDyV(indinters,medio+1,f);
		fusion=auxMaxSolDyV(indinters,p,f);
	}
	if(mitadMenor.solape>=mitadMayor.solape && mitadMenor.solape>=fusion.solape){//Casos base
		return mitadMenor;
	}
	else if(mitadMayor.solape>=mitadMenor.solape && mitadMayor.solape>=fusion.solape){
		return mitadMayor;
	}
	else{
		return fusion;
	}
}



