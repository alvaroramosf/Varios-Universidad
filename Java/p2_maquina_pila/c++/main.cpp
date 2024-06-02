//Autor: Álvaro Ramos Fustero    ~   844798. 
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Instruccion {
public:
	virtual void ejecutar(stack<int>& pila, int& contador) = 0;
	virtual string toString() = 0;
	virtual ~Instruccion() {}
};

class push : public Instruccion {
private:
	int valor;
public:
	push(int valor) : valor(valor) {}
	void ejecutar(stack<int>& pila, int& contador) {
		pila.push(valor);
		contador++;
	}
	string toString() {
		return "push " + to_string(valor);
	}
};

class pop : public Instruccion {
public:
	void ejecutar(stack<int>& pila, int& contador) {
	if (!pila.empty()) {
		pila.pop();
	}
	contador++;
	}
	string toString() {
		return "pop";
	}
};

class add : public Instruccion {
public:
	void ejecutar(stack<int>& pila, int& contador) {
		if (pila.size() >= 2) {
			int a = pila.top();
			pila.pop();
			int b = pila.top();
			pila.pop();
			pila.push(a + b);
		}
		contador++;
	}
	string toString() {
		return "add";
	}
};

class read : public Instruccion {
public:
	void ejecutar(stack<int>& pila, int& contador) {
		int valor;
		cout << "?";
		cin >> valor;
		pila.push(valor);
		contador++;
	}
 	string toString() {
		return "read";
	}
};

class write : public Instruccion {
public:
	void ejecutar(stack<int>& pila, int& contador) {
		if (!pila.empty()) {
			int valor = pila.top();
			pila.pop();
			cout << valor << endl;
		}
		contador++;
	}
	string toString() {
		return "write";
	}
};

class dup : public Instruccion {
public:
	void ejecutar(stack<int>& pila, int& contador) {
		if(!pila.empty()){
			int value = pila.top(); pila.pop();
			pila.push(value);
			pila.push(value);
		}
	contador++;
	}
	string toString() {
	return "dup";
	}
};

class jumpif : public Instruccion {
private:
	int direccion;
public:
	jumpif(int direccion) : direccion(direccion) {}
	void ejecutar(stack<int>& pila, int& contador){
		if(!pila.empty()){
			int value = pila.top(); pila.pop();
			if(value>=0){
				contador=direccion;
			}
			else{
				contador++;
			}
		}
	}
	string toString() {
		return "jumpif " + to_string(direccion);
	}
};

class mul : public Instruccion {
public:
	void ejecutar(stack<int>& pila, int& contador) {
		if (pila.size() >= 2) {
			int a = pila.top();
			pila.pop();
			int b = pila.top();
			pila.pop();
			pila.push(a * b);
		}
		contador++;
	}
	string toString() {
		return "mul";
	}
};

class sw : public Instruccion {
public:
	void ejecutar(stack<int>& pila, int& contador) {
		if (pila.size() >= 2) {
			int a = pila.top();
			pila.pop();
			int b = pila.top();
			pila.pop();
			pila.push(a);
			pila.push(b);
		}
		contador++;
	}
	string toString() {
		return "mul";
	}
};


class over : public Instruccion {
public:
	void ejecutar(stack<int>& pila, int& contador) {
		if (pila.size() >= 2) {
			int a = pila.top();
			pila.pop();
			int b = pila.top();
			pila.pop();
			pila.push(b);
			pila.push(a);
			pila.push(b);
			}
			contador++;
		}
		string toString() {
			return "over";
		}
};

class Programa {
protected:
	vector<Instruccion*> instrucciones;
	int numInstrucciones;
public:
	Programa() : instrucciones(), numInstrucciones(0) {}
	void ejecutar() {
		cout<<"Ejecucion: \n";
		stack<int> pila;
		int contador = 0;
		while (contador >= 0 && contador < numInstrucciones) {
			instrucciones[contador]->ejecutar(pila, contador);
		}
	}
	void listar() {
		cout<<"Programa: \n";
		for (int i = 0; i < numInstrucciones; i++) {
			cout << i << ": " << instrucciones[i]->toString() << endl;
		}
	}
	virtual ~Programa() {
		for (int i = 0; i < numInstrucciones; i++) {
		delete instrucciones[i];
		}
	}
};

class ProgramaEjemplo : public Programa {
public:
ProgramaEjemplo(int i) {
	if(i==0){ //Suma
		instrucciones.push_back(new read());
		instrucciones.push_back(new read()); 
		instrucciones.push_back(new add());
		instrucciones.push_back(new write());
		numInstrucciones = instrucciones.size();
	}
	if(i==1){ //Cuenta Atrás
		instrucciones.push_back(new read());//Esto no va??
		instrucciones.push_back(new dup);//Quitar 
		instrucciones.push_back(new write);
		instrucciones.push_back(new push(-1));
		instrucciones.push_back(new add());
		instrucciones.push_back(new dup());
		instrucciones.push_back(new jumpif(1));
		numInstrucciones = instrucciones.size();
	}
	if(i==2){//Factorial
		instrucciones.push_back(new push(1));
		instrucciones.push_back(new read()); 
		instrucciones.push_back(new sw());//Lo pongo así por que si pongo swap lo confunde con swap de <stack>
		instrucciones.push_back(new over());
		instrucciones.push_back(new mul());
		instrucciones.push_back(new sw());
		instrucciones.push_back(new push(-1));
		instrucciones.push_back(new add());
		instrucciones.push_back(new dup());
		instrucciones.push_back(new push(-2));
		instrucciones.push_back(new add());
		instrucciones.push_back(new jumpif(2));
		instrucciones.push_back(new sw());
		instrucciones.push_back(new write());
		numInstrucciones = instrucciones.size();
	}
}
};

int main() {
	for(int i=0; i<3; i++){
		Programa* programa = new ProgramaEjemplo(i);
		programa->listar();
		programa->ejecutar();
		delete programa;
		cout << "\n";
	}
	return 0;
}


