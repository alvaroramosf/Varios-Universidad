import java.util.ArrayList;
import java.util.List;
import java.util.Iterator;

// Clase Nodo (superclase)
abstract class Nodo {
	protected String nombre;
	protected String rutaPadre;
	protected Directorio padre;
	boolean root = false;
	
	public Nodo(String nombre, Directorio padre) {//Constructor
		if (nombre == null || nombre.isEmpty() || nombre.contains(" ") || nombre.contains("/")) {
			;//break, nombre no es valido
		}
		this.nombre = nombre;
		this.padre = padre;
		this.root = false;
		
	}
	
	public Nodo() {//Constructor
		this.root = true;
	}
	
	public String getNombre(){
		return this.nombre;
	}
	
	abstract int getTamagno();
	
	public String getRuta(){//Obtener la ruta del nodo
		if(this.root){
			return "~/";
		}else if(this.padre.root){
			return "~/" + this.nombre;
		}else{
			return this.padre.getRuta() + "/" + nombre;
		}
	}
}

// Subclase Directorio
class Directorio extends Nodo {
	private int iterador;
	private List<Nodo> subNodos;
	
	public Directorio(String nombre, Directorio padre){
		super(nombre, padre);
		//this.tamagno = 0;
		this.padre = padre; //Get directorio actual (Añadimos al padre)
		this.subNodos = new ArrayList<>();//Creamos la lista de subdirectorios de este directorio
	}
	
	public Directorio(){//Si no tiene padre (root)
		super();
		//this.tamagno = 0;
		this.subNodos = new ArrayList<>();//Creamos la lista de subdirectorios de este directorio
	}
	
	public Directorio getPadre(){
		return this.padre;
	}
	
	public boolean existHijo(String nombre){//Devuelve true si el directorio contiene algún subnodo
		for (Nodo nodo : subNodos) {
			if (nodo.getNombre().equals(nombre)) {
				return true;
			}
		}
		return false;
	}
	
	public Nodo getHijo(String nombre){//Devuelve el subnodo con el nombre dado QUITAR
		for (Nodo nodo : subNodos) {
			if (nodo.getNombre().equals(nombre)) {
				return nodo;//Devolver el nodo, aunque no se muy bien como
			}
		}
		return null;
	}
	
	public void makeDirHijo(String nombre){//Crea un nodo hijo con el nombre dado
			this.subNodos.add(new Directorio(nombre, this));
	}
	
	public void makeFileHijo(String nombre, int tamagno){//Crea un nodo hijo con el nombre dado
		if(!this.existHijo(nombre)){
			this.subNodos.add(new Fichero(nombre, this, tamagno));//Esto no se si esta bien
		}
	}
	
	public void linkHijo(String nombre, Nodo destino){//Crea un nodo hijo con el nodo dado. Usado para los enlaces.
		if(!this.existHijo(nombre)){
			this.subNodos.add(new Enlace(nombre, this, destino));//Esto no se si esta bien
		}
	}


	@Override
	public int getTamagno(){
		int tamagno = 0;
		for (Nodo nodo : subNodos){
			if (nodo instanceof Fichero || nodo instanceof Enlace){
				tamagno = tamagno + nodo.getTamagno();
			} else if (nodo instanceof Directorio){
				tamagno = tamagno + ((Directorio) nodo).getTamagno();
			}
		}
		return tamagno;
	}
	
	
	//OPERACIONES DEL ITERADOR
	public void iniciarIterador(){
		iterador = 0;
	}
	
	public boolean existeSiguiente(){
		if(iterador < subNodos.size()){//lista.get(indice)
			return true;
		}else{
			return false;
		}
	}
	
	public Nodo getSiguiente(){
		Nodo output = subNodos.get(iterador);
		iterador++;
		return output;
	}
	
}

// Subclase Fichero
class Fichero extends Nodo {
	private int tamagno;
	
	public Fichero(String nombre, Directorio padre, int tamagno){
		super(nombre, padre);
		this.tamagno = tamagno;
	}
	
	@Override
	public int getTamagno(){
		return tamagno;
	}
}

// Subclase Enlace
class Enlace extends Nodo {
	Nodo rutaEnlazada;//Ruta del nodo al que enlaza
	
	public Enlace(String nombre, Directorio padre, Nodo rutaEnlazada){
		super(nombre, padre);
		this.rutaEnlazada = rutaEnlazada;
	}
	
	@Override
	public int getTamagno(){
		return 1;//Devuelve el tamaño del enlace, aqui he puesto uno pero no se cuanto es.
	}

}

