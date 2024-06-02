//Autor: Álvaro Ramos Fustero ~ 855798

import java.util.Stack;
import java.util.Scanner;


abstract class Instruccion{
	protected static Stack<Object> pilaCompartida = new Stack<>();//Pila compartida
	protected static int pc;	
	protected static void push(Object item) { // Métodos para operar la pila
		pilaCompartida.push(item);
	}
	protected static Object pop() {
		return pilaCompartida.pop();
	}
	
	//Lista la instruccion
	 public void listar(){
		System.out.println(this.getClass().getSimpleName());//Obtenemos el nombre de la clase hija
	}
	

	public int getPC(){
		return pc;
	}
	
	//Devuelve true si el programa no ha llegado al final
	public boolean continuarPrograma(int size){
		if(pc < size) return true;
		else return false;
	}
	
	public abstract void ejecutar();
}

class Inicializar extends Instruccion {
	@Override
	public void ejecutar() {
		pilaCompartida.clear();
		pc = 0;
	}
}

class Add extends Instruccion {
	@Override
	public void ejecutar() {
		int a = (int) pilaCompartida.pop();
		int b = (int) pilaCompartida.pop();
		pilaCompartida.push(a+b);
		pc++;
	}
}

class Read extends Instruccion {
	@Override
	public void ejecutar() {
		Scanner sc = new Scanner(System.in);
		System.out.print("?");
		int valor = sc.nextInt();
		pilaCompartida.push(valor);
		pc++;
	}
}

class Write extends Instruccion {
	@Override
	public void ejecutar() {
		if (!pilaCompartida.empty()) {
			int valor = (int) pilaCompartida.pop();
			System.out.println(valor);
		}
		pc++;
	}
}

class Push extends Instruccion {
	private int a;

	public Push(int a){
		this.a = a;
	}
	
	@Override
	public void ejecutar() {
		pilaCompartida.push(a);
		pc++;
	}
	
	@Override
	public void listar(){
		System.out.println(getClass().getSimpleName()+" "+a);
	}
}

class Dup extends Instruccion {
	@Override
	public void ejecutar() {
		int a = (int) pilaCompartida.pop();
		pilaCompartida.push(a);
		pilaCompartida.push(a);
		pc++;
	}
}

class Jumpif extends Instruccion {
	private int c;

	public Jumpif(int c){
		this.c = c;
	}
	
	@Override
	public void ejecutar() {
		if (!pilaCompartida.empty()) {
			int value = (int) pilaCompartida.pop();
			if (value >= 0) {
				pc = c;
			} else {
				pc++;
			}
		}
	}
	
	@Override
	public void listar(){
		System.out.println(getClass().getSimpleName()+" "+c);
	}
}


class Mul extends Instruccion {
	@Override
	public void ejecutar() {
		int a = (int) pilaCompartida.pop();
		int b = (int) pilaCompartida.pop();
		pilaCompartida.push(a*b);
		pc++;
	}
}

class Swap extends Instruccion {
	@Override
	public void ejecutar() {
		int a = (int) pilaCompartida.pop();
		int b = (int) pilaCompartida.pop();
		pilaCompartida.push(a);
		pilaCompartida.push(b);
		pc++;
	}
}

class Over extends Instruccion {
	@Override
	public void ejecutar() {
		if (pilaCompartida.size() >= 2) {
			int a = (int) pilaCompartida.pop();
			int b = (int) pilaCompartida.pop();
			pilaCompartida.push(b);
			pilaCompartida.push(a);
			pilaCompartida.push(b);
		}
		pc++;
	}
}
