//------------------------------------------------------------------------------
// File:   main_p2_e1.cpp
// Date:   septiembre 2023
// Coms:   Parte del práctica 1 de PSCD
//         Compilar mediante
//           g++ main_p2_e1.cpp -o main_p2_e1 -std=c++11 -pthread
//------------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <atomic>
using namespace std;

const int N = 512;
const int N_BUSC = 8; //# de procesos buscadores
using VectInt = int[N]; //"VectInt" es un "alias" para vector de int de dim. N

//-----------------------------------------------------
//Pre: 0 ≤ i ≤ d ≤ N − 1
//Post: result = N um α ∈ [i, d].value = v[α] 8 
void search(const VectInt v,
    const int i, const int d, const int value,
    int& maxVeces, int& indMin, int& indMax,
    atomic_flag& tas){
    int nVecesAux=0;
    for(int j = i; j < d+1; j++){
        if(value == v[j]){
            nVecesAux ++;
            if(nVecesAux > maxVeces){
                while (tas.test_and_set(memory_order_acquire)); // Inicio Exclusión mutua
                indMin=i;
                indMax=d;
                maxVeces=nVecesAux;
                tas.clear(memory_order_release); // Fin Exclusión mutua
            }
        }
    }
}

//Pre: ---
//Post: carga los datos del fichero de nombre <nomfichero> en el vector <v>.
void cargarDatos(VectInt v,const string nomFichero){
    ifstream f;
    f.open(nomFichero);
    if(f.is_open()){
        int i=0;
        f>>v[i];
        while(!f.eof()){
            i++;
            f>>v[i];
        }
        f.close();
    }else{
        cerr<<"No se ha podido cargar los datos"<<endl;
    }
}
//Pre: ---
//Post: Ha cargado los datos del fichero en el vector <v>, avisa a los procesos buscadores
//      que están cargados,ha esperado a que cada proceso buscador termine su trabajo y muestra
//      por salida estándar el número total de veces que aparece el valor buscado en el vector y el 
//      trozo del vector donde se encuentra.

void coordinador(const int nBuscar, int & maxVeces, VectInt v, bool  buscadorTerminado[], bool & datosCargados, int & indMin, int & indMax){
    cargarDatos(v, "datos.txt");
    cout<<"Datos cargados... \n";
    datosCargados=true;
    for(int i=0; i < N_BUSC; i++){//Espera activa a que terminen los buscadores
        while(buscadorTerminado[i]==false){this_thread::yield();};
    }
    cout<<"El número " << nBuscar << " aparece un máximo de " << maxVeces << " en un vector situado situado entre " << indMin << " y " << indMax <<" \n";
}
//Pre: ---
//Post: Espera a que el proceso coordinador haya cargado los datos, asigna a <i> y <d> valores, luego ejecuta 
//      la función search y avisa al coordinador de que ha finalizado su trabajo.
void buscador(const int nBuscador, const int nBuscar, int  & maxVeces ,VectInt v, bool  buscadorTerminado[], bool & datosCargados, int & indMin, int & indMax, atomic_flag& tas){
    while(datosCargados==false){this_thread::yield();};//Espera activa a que los datos estén cargados
    int blockSize = N / N_BUSC;
    int i = nBuscador * blockSize;
    int d = (nBuscador + 1) * blockSize - 1;

    search(v, i, d, nBuscar, maxVeces, indMin, indMax, ref(tas));
    buscadorTerminado[nBuscador]= true;
}
//Pre: ---
//Post: Dado un número entre 1 y 25 que ha elegido el usuario, muestra por pantalla el número de veces
//      que aparece en el fichero <datos.txt>    
int main(){
    int nBuscar;
    int maxVeces=0;
    int indMin, indMax;
    VectInt v;
    bool datosCargados= false;
    bool buscadorTerminado[N_BUSC] = {false};
    atomic_flag tas = ATOMIC_FLAG_INIT;
  
    //solicitar datos al usuario
    cout << "Introduce nº [1 .. 25] a buscar: ";
    cin >> nBuscar;
  
    //lanzar procesos
    thread Tcoord(&coordinador, nBuscar, ref(maxVeces), ref(v), ref(buscadorTerminado), ref(datosCargados),  ref(indMin), ref(indMax));
    thread busc[N_BUSC];
    for(int i = 0; i < N_BUSC; i++){
        busc[i] = thread (&buscador, i, nBuscar, ref(maxVeces), ref(v), ref(buscadorTerminado), ref(datosCargados), ref(indMin), ref(indMax), ref(tas));
    }
    for (int i=0; i<N_BUSC; i++) { 
        busc[i].join(); //me bloqueo hasta que "P[i]" termine
    }
    Tcoord.join();  //esperar a que los procesos terminen
    return 0;
}



