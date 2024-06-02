//Autor: Álvaro Ramos Fustero ~ 844798
//Clase anagrama, represanta a un conjunto de palabras que forman un anagrama

import java.util.ArrayList;

public class Anagrama{
	private ArrayList<String> anagramas;
	private int iterador;
	
	public Anagrama(String palabra){//Nuevo anagrama
	this.anagramas = new ArrayList<>();
	this.anagramas.add(palabra);
	}
	
	public void agnadirAnagrama(String palabra) {//Nueva palabra
		this.anagramas.add(palabra);
	}
	
	public int getNumPalabras(){//Numero de palabras que contiene
		return this.anagramas.size();
	}
	
	//Operaciones necesarias para la implementación de un iterador.
	public String getPrimeraPalabra(){
		if(!anagramas.isEmpty()){
			this.iterador=0;
			return this.anagramas.get(this.iterador++);
		}
		else return "error";
	}
	
	public String getPalabra(){
		if(!anagramas.isEmpty()){
			return this.anagramas.get(this.iterador++);
		}
		else return "error";
	}
	
	public boolean existeSiguientePalabra(){
		return this.iterador < this.anagramas.size();
	}
}
