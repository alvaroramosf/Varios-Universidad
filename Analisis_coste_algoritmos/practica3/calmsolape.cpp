//*****************************************************************
// Author: Álvaro Ramos Fustero NIP:844798
//*****************************************************************
#include <iostream>

using namespace std;

#include "maxsolape.hpp"

double inters[N][2] = {
	{1.5, 8.0},
        {0.0, 4.5},
       {2.0, 4.0},
       {1.0, 6.0},
        {3.5, 7.0},
        {1.5, 8.0},
        {0.0, 4.5},
       {2.0, 4.0},
       {2.0, 6.0},
        {3.5, 7.0},
        {1.5, 8.0},
        {0.0, 4.5},
       {2.0, 4.0},
       {1.0, 6.0},
        {3.5, 7.0},
        {1.5, 8.0},
        {0.0, 9.5},
       {2.0, 4.0},
       {4.0, 6.0},
        {3.5, 7.0}
   };
 
 int n=20;

void movInterA(tpInter destino, tpInter origen){
	destino.ind=origen.ind;
	destino.ini=origen.ini;
	destino.fin=origen.fin;
}

int main(){

tpInter vector[n];
crearvind(inters, vector, n);
for (int i=0; i<n; i++){
cout<<vector[i].ind<<"  "<<vector[i].ini<<"  "<<vector[i].fin<<"  "<<endl;}



mergesortIndInters(vector, 0, n-1);
for (int i=0; i<n; i++){
cout<<vector[i].ind<<"  "<<vector[i].ini<<"  "<<vector[i].fin<<"  "<<endl;}

double i=maxSolFBruta(inters,n).solape;
double j=maxSolFBruta(inters,n).interA;
double k=maxSolFBruta(inters,n).interB;

cout<<i<<"  "<<j<<"  "<<k<<"  (fuerzaBruta)"<<endl;

i=maxSolDyV(vector,0,n-1).solape;
j=maxSolDyV(vector,0,n-1).interA;
k=maxSolDyV(vector,0,n).interB;
cout<<i<<"  "<<j<<"  "<<k<<"  (DyV)"<<endl;

return 0;
}

