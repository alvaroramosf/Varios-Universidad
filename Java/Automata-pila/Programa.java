//Autor: Álvaro Ramos Fustero ~ 855798

import java.util.ArrayList;
import java.util.Stack;

class Programa {
	private ArrayList<Instruccion> programa;
	public Programa(int n) {//Constructor, para seleccionar programa
		programa = new ArrayList<>();
		if(n==1){//PROGRAMA 2
		programa.add(new Read());
		programa.add(new Read());
		programa.add(new Add());
		programa.add(new Write());
		}
		
		if(n==2){//PROGRAMA 2
		programa.add(new Read());
		programa.add(new Dup());
		programa.add(new Write());
		programa.add(new Push(-1));
		programa.add(new Add());
		programa.add(new Dup());
		programa.add(new Jumpif(1));
		}
		
		if(n==3){//PROGRAMA 3
		programa.add(new Push(1));
		programa.add(new Read());
		programa.add(new Swap());
		programa.add(new Over());
		programa.add(new Mul());
		programa.add(new Swap());
		programa.add(new Push(-1));
		programa.add(new Add());
		programa.add(new Dup());
		programa.add(new Push(-2));
		programa.add(new Add());
		programa.add(new Jumpif(2));
		programa.add(new Swap());
		programa.add(new Write());
		}
	}
	
	public void ejecutarPrograma() {
		System.out.println("Ejecución:");
		Inicializar start = new Inicializar();
		start.ejecutar();
		Instruccion instruccionActual;
		//System.out.println(programa.size());
		do{
			instruccionActual = programa.get(start.getPC());
			//System.out.println(start.getPC());
			instruccionActual.ejecutar();
		} while (instruccionActual.continuarPrograma(programa.size()));
	}

	public void listarPrograma() {
		System.out.println("Programa:");
		for (Instruccion instruccionActual : programa) {
			instruccionActual.listar();
		}
	}
}

