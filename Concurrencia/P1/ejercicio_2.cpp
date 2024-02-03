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

using namespace std;

/*
  Pre: ...
  Post: devuelve un número aleatorio entre los numeros enteros a y b
*/
int aleatorio(const int a, const int b){
  return (a+rand()%(b+1-a));
}

/*
  Pre: 
  Post: Muestra por pantalla un mensaje "veces" número de veces y bloquea el thread "retardo" número de milisegundos
*/
void saludo(int id, int retardo, int veces) {
    for(int i=1; i<=veces; i++) {
        //cout << "Soy " << id << endl;
        cout << "Soy " + to_string(id) + "\n";
        //el thread que me ejecuta se bloquea durante "retardo" milisegundos
        this_thread::sleep_for(chrono::milliseconds(retardo));
    }
}
/*
  Pre: ...
  Post: Se lanzan 10 procesos, así el proceso i-ésimo se duerme durante un tiempo aleatorio  entre 100 y 300 milisegundos,
        y escribe el mensaje correspondiente (“Soy 1”,“Soy2”,. . . ,“Soy 10”) un número aleatorio de veces, entre 5 y 15.
*/
int main(int argc, char* argv[]) {
    const int N = 10;
    thread P[N]; //de momento, ningún thread se pone en marcha


    for (int i=0; i<N; i++) { 
        P[i] = thread(&saludo, i, aleatorio(100,300), aleatorio(5,15));
    }

    for (int i=0; i<N; i++) { 
        P[i].join(); //me bloqueo hasta que "P[i]" termine
    }

    cout << "Fin\n";
    return 0;
}
