import java.util.ArrayList;
import java.util.List;

// Clase abstracta que representa cualquier objeto mercancía en un contenedor o camión determinado
abstract class Mercancia {
    // Variables que definen la mercancía
    protected String nombre;
    protected double volumen;
    protected double peso;

    // Constructor
    public Mercancia(String nombre, double volumen, double peso) {
        this.nombre = nombre;
        this.volumen = volumen;
        this.peso = peso;
    }

    // Método abstracto para obtener el tipo de carga
    public abstract String tipo();

    // Método para obtener el nombre de la mercancía
    public String nombre() {
        return nombre;
    }

    // Método para obtener el volumen de la mercancía
    public double volumen() {
        return volumen;
    }

    // Método para obtener el peso de la mercancía
    public double peso() {
        return peso;
    }

    // Método para obtener la representación textual de la mercancía
    public String toString() {
        return nombre + " [" + String.format("%.4f", volumen) + " m3] [" + String.format("%.4f", peso) + " kg]\n";
    }
}

// Clase que representa un SerVivo
class SerVivo extends Mercancia {
    // Constructor
    public SerVivo(String nombre, double volumen, double peso) {
        super(nombre, volumen, peso);
    }

    // Método para obtener el tipo de carga
    public String tipo() {
        return "de Seres Vivos.";
    }
}

// Clase que representa un producto tóxico
class Toxico extends Mercancia {
    // Constructor
    public Toxico(String nombre, double volumen, double peso) {
        super(nombre, volumen, peso);
    }

    // Método para obtener el tipo de carga
    public String tipo() {
        return "de Producto Toxico.";
    }
}

// Clase que representa una carga normal
class Carga extends Mercancia {
    // Constructor
    public Carga(String nombre, double volumen, double peso) {
        super(nombre, volumen, peso);
    }

    // Método para obtener el tipo de carga
    public String tipo() {
        return "de Carga Estandar.";
    }
}

// Clase que representa un producto
class Producto extends Carga {
    // Constructor
    public Producto(String nombre, double volumen, double peso) {
        super(nombre, volumen, peso);
    }
}

// Clase abstracta que representa un almacén
abstract class Almacen<T extends Mercancia> {
    protected double capacidad; // Capacidad del almacén
    protected List<T> elementos; // Lista de elementos

    // Constructor
    public Almacen(double capacidad) {
        this.capacidad = capacidad;
        elementos = new ArrayList<>();
    }

    // Método para obtener la capacidad del almacén
    public double capacidad() {
        return capacidad;
    }

    // Método abstracto para guardar un objeto en el almacén
    public abstract boolean guardar(T objeto);
}

// Clase que representa un contenedor
class Contenedor<T extends Mercancia> extends Carga {
    private Almacen<T> almacen;

    // Constructor
    public Contenedor(double capacidad) {
        super("Contenedor", capacidad, 0.0);
        almacen = new Almacen<T>(capacidad) {
            // Implementación del método guardar para el contenedor
            public boolean guardar(T objeto) {
                double volumenTotal = 0.0;
                for (T elemento : elementos) {
                    volumenTotal += elemento.volumen();
                }
                double volumenNuevoObjeto = objeto.volumen();
                double volumenFinal = volumenTotal + volumenNuevoObjeto;
                boolean cabe = volumenFinal <= capacidad;
                if (cabe) {
                    elementos.add(objeto);
                }
                return cabe;
            }
        };
    }

// Clase que representa un camión
class Camion extends Almacen<Carga> {
    private String nombre;

    // Constructor
    public Camion(double capacidad) {
        super(capacidad);
        nombre = "Camion";
    }

    // Método para obtener el nombre del camión
    public String nombre() {
        return nombre;
    }

    // Método para obtener el peso del camión
    public double peso() {
        double pesoTotal = 0.0;
        for (Carga carga : elementos) {
            pesoTotal += carga.peso();
        }
        return pesoTotal;
    }

    // Implementación del método guardar para el camión
    @Override
    public boolean guardar(Carga carga) {
        double volumenTotal = 0.0;
        for (Carga elemento : elementos) {
            volumenTotal += elemento.volumen();
        }
        double volumenNuevoObjeto = carga.volumen();
        double volumenFinal = volumenTotal + volumenNuevoObjeto;
        boolean cabe = volumenFinal <= capacidad;
        if (cabe) {
            elementos.add(carga);
        }
        return cabe;
    }
}


}

