//------------------------------------------------------------------------------
// File:   practica_1_V2.cpp
// Date:   septiembre 2023
// Coms:   Parte del práctica 1 de PSCD
//         Compilar mediante
//           g++ practica_1_V2.cpp -o practica_1_V2 -std=c++11 -pthread
//------------------------------------------------------------------------------
#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <cstdlib>
#include <tgmath.h>

#include <functional>

using namespace std;

/*
  Pre: ...
  Post: devuelve un número aleatorio entre los numeros enteros a y b
*/
int aleatorio(const int a, const int b){
  return (a+rand()%(b+1-a));
}
/*
  Pre: Reales es un vector de números reales con n componentes
  Post: Asigna a media la media de todas las componentes del vector y al acabar pone media_lista a true
*/
void calcular_media(double reales[], int N, double& media, bool& media_lista){
  media=0;
  for (int i=0; i<N; i++) { 
       media = media + reales[i];
  }
  media=media/N;
  media_lista=true;
  return;
  }

/*
  Pre: Reales es un vector de números reales con n componentes
  Post: Asigna en min y en max el menor y mayor número del vector reales respectivamente
*/
void calcular_minmax(double reales[], int N, double& min, double& max){
  min=reales[0];
  max=reales[0];
  for (int i=0; i<N; i++) { 
      if(reales[i]<min){
        min=reales[i];
        }
      else if(reales[i]>max){
        max=reales[i];
        }
      }
  return;
  }
  
/*
  Pre: Reales es un vector de números reales con n componentes
  Post: Cuando se ha acabado de calcular la media, por lo que media_lista es verdadera, calcula la desviacion típica 
  y la asigna a desvtipica
*/
void calcular_desvtipica(double reales[], bool& media_lista, double& media, int N, double& desvtipica){
  desvtipica = 0;
  
  while(!media_lista){;}
  
  for (int i=0; i<N; i++) { 
       desvtipica +=  pow((reales[i]-media),2);
  }
  desvtipica=sqrt(desvtipica / N);
  return;
  }
  

/*
  Pre: ...
  Post: Crea un vector de 100 números reales aleatorios y lanza 3 procesos para calcular la media, desviación típica 
  y el mínimo y máximo del vector, posteriormente saca los resultados por pantalla
*/

int main(int argc, char* argv[]) {
    int N = 100;
    double min, max, media, desvtipica;
    bool media_lista=false;
    double reales[100]; //cambiar
    for (int i=0; i<N; i++) { 
        reales[i] = (aleatorio(0, 2000000)/1000.0)/2.0;//preguntar
        cout<<reales[i]<<"\n";
    }
  thread Tmedia(&calcular_media, reales, N, ref(media), ref(media_lista));
  thread Tminmax(&calcular_minmax, reales, N, ref(min), ref(max));
  thread Tdesvtipica(&calcular_desvtipica, reales, ref(media_lista), ref(media), N, ref(desvtipica));

  Tmedia.join();
  Tminmax.join();
  Tdesvtipica.join();
  
  cout << "# datos:" << N << "\n"<< "media:" << media << "\n"<< "máx:" << max << "\n" << "min:" << min << "\n" << "sigma:" << desvtipica << "\n";
    return 0;
}
