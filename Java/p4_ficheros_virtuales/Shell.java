import java.util.ArrayList;

class Shell {
	Directorio root;//Directorio raiz
	Directorio dirActual;//Directorio en el que se encuentra el shell

	public Shell(){//Constructor, creamos el root.
		this.root = new Directorio();
		this.dirActual = this.root;
	}
	
	public String pwd(){//Devuelve la representación textual de la ruta desde la raíz al directorio actual de trabajo
		return dirActual.getRuta();
	}
	
	public String ls(){//Devuelve un listado con el nombre de todos los nodos contenidos en el directorio actual, uno por línea
		String output  = "";
		this.dirActual.iniciarIterador();
		while(dirActual.existeSiguiente()){
			output = output + "\n" + this.dirActual.getSiguiente().getNombre();
		}
		return output;	
	}
	
	public String du(){//Devuelve un listado con el nombre y el tamaño de todos los nodos contenidos en el directorio actual, uno por línea.
		String output  = "";
		this.dirActual.iniciarIterador();
		while(this.dirActual.existeSiguiente()){
			Nodo iterando = this.dirActual.getSiguiente();
			output = output + "\n" + iterando.getNombre() + "  " + iterando.getTamagno();
		}
		return output;
	}
	
	public void mkdir(String nombre){//Crea un directorio de nombre 'name' en el directorio activo.
		if(!this.dirActual.existHijo(nombre)){
			this.dirActual.makeDirHijo(nombre);
		}
	}
	
	public void vi(String nombre, int tamagno){//Edita el fichero de nombre 'name' (en el directorio actual)
		if(!this.dirActual.existHijo(nombre)){
		this.dirActual.makeFileHijo(nombre, tamagno);//Hacer que no solo cree, también edite
		}else{//Editar
		
		;
		}
	}
	
	private static ArrayList<String> descomponerRuta(String cadena) {
		ArrayList<String> partes = new ArrayList<>();
		StringBuilder sb = new StringBuilder();

 		for (int i = 0; i < cadena.length(); i++) {
			char caracter = cadena.charAt(i);
			if (caracter == '/') {// Si encontramos "/", agregamos la parte actual a la lista y reiniciamos el StringBuilder
				partes.add(sb.toString());
				sb = new StringBuilder();
			} else {
				// Si no encontramos "/", agregamos el carácter al StringBuilder
				sb.append(caracter);
			}
		}
		// Agregamos la última parte al ArrayList
		partes.add(sb.toString());
		return partes;
	}
	
	
	private Nodo obtenerNodo(String ruta){
		Nodo nodo;
		if(ruta.startsWith("/")){//Es una ruta absoluta.
			nodo = this.root;
		}else{//Es ruta relativa, seguimos en este directorio
			nodo = this.dirActual;
		}
		ArrayList<String> rutaDescompuesta = descomponerRuta(ruta);//Descomponemos la ruta
    
		for (String parte : rutaDescompuesta) {
			if(parte.equals("..")){
			nodo = ((Directorio)nodo).getPadre();
			}else if(parte.equals(".")){
				// No hacer nada
			}else if(((Directorio)nodo).existHijo(parte)){
			nodo = ((Directorio)nodo).getHijo(parte);
			}else{
			// Manejar el caso en el que no se encuentra el nodo
			}
		}	
		return nodo;
	}

	
	/*private Nodo obtenerNodo(String ruta){
	
	}*/

	public String stat(String ruta){
		Nodo nodoActual = obtenerNodo(ruta);
		return String.valueOf(nodoActual.getTamagno());
	}
	//System.out.println("Error sintactico: comando desconocido");



	
	public void cd(String ruta){//Cambia el directorio de trabajo (directorio actual)
		//Falta comprobar si es un directorio
		this.dirActual = (Directorio)obtenerNodo(ruta);
        }

	
	public void ln(String nombre, String ruta){//Crea en el directorio actual un enlace simbólico de nombre 'name' que apunta al elemento identificado mediante la ruta especificada en 'path'
		if(!this.dirActual.existHijo(nombre)){
			this.dirActual.linkHijo(nombre, obtenerNodo(ruta));
		}else{
			// Manejar el caso en el que el hijo ya existe
		}
	}
	
	public void rm(String nombre){//Elimina un nodo
		//Borrar subnodos etc (FALTA)
	}
}
