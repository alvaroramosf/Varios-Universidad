//Autor: Álvaro Ramos Fustero ~ 844798
//Main, código que recorre los anagramas.

import java.util.ArrayList;
import java.util.Collections;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;


public class ColeccionAnagramas {
	private static ArrayList<Anagrama> coleccion = new ArrayList<>();//Todos los anagramas que encontramos

	//Método que dice si dos arraylists de carácteres son un anagrama el uno de oyto
	public static boolean sonAnagramas(ArrayList<Character> list1, ArrayList<Character> list2) {
		if (list1.size() != list2.size()) {// Verificar si los tamaños de las listas son diferentes
			return false;
		}
		ArrayList<Character> copy1 = new ArrayList<>(list1);
		ArrayList<Character> copy2 = new ArrayList<>(list2);
		Collections.sort(copy1);// Ordenar las copias de las listas
		Collections.sort(copy2);

		// Verificar si las listas ordenadas son iguales
		return (copy1.equals(copy2));
	}
	
	//Añade
	
	public static void agnadirPalabra(String palabra){
		ArrayList<Character> palabraCaracteres = new ArrayList<>();
		for (char c : palabra.toCharArray()) {//palabra -> array de letras
			palabraCaracteres.add(c);
		}
		boolean anagramaEncontrado = false;
		for (Anagrama anagrama : coleccion) {//Comparamos la palabra que hemos leido con todos los anagramas existentes, si existe lo añadimos y si no lo creamos
			ArrayList<Character> palabraAnagrama = new ArrayList<>();
			for (char c : anagrama.getPrimeraPalabra().toCharArray()) {
				palabraAnagrama.add(c);
			}
			if (sonAnagramas(palabraAnagrama, palabraCaracteres)) {
				anagrama.agnadirAnagrama(palabra);
				anagramaEncontrado = true;
				System.out.println("Palabra: " + palabra + " añadida al anagrama " + anagrama.getPrimeraPalabra());
				break;
			}
		}
		if (!anagramaEncontrado) {
			coleccion.add(new Anagrama(palabra));
		}
	}
	

	//Muestra los anagramas por pantalla
	public static void mostrarAnagramas(ArrayList<Anagrama> coleccion, int n){
		for (Anagrama anagrama : coleccion) {//Mostrar por pantalla los anagramas con al menos n palabras
				if(anagrama.getNumPalabras()> n){//Por ejemplo, anagramas de más de 2 palabras (si no no son anagramas)
					System.out.println("Anagramas formados por las letras de  \"" + anagrama.getPrimeraPalabra() + "\" : ");
					while(anagrama.existeSiguientePalabra()){
						System.out.print(anagrama.getPalabra()+",");
					}
					System.out.println();
				}
		}
	}

	public static void main(String[] args) {
		String filePath = "/usr/share/dict/spanish";
		try {
			BufferedReader reader = new BufferedReader(new FileReader(filePath));
			String palabraLeida;
			while ((palabraLeida = reader.readLine()) != null) {//Leemos palabra
				agnadirPalabra(palabraLeida);
			}
			reader.close();
			mostrarAnagramas(coleccion, 2);
		} catch (IOException e) {
			System.err.println("Error al leer el archivo diccionario, puede ser que no exista en tu S.O.: " + e.getMessage());
		}
	}
}

