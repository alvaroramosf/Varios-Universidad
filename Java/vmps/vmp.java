//Autor: Álvaro Ramos Fustero ~ 855798

public class vmp {
	private int id;
	private double[] location; // Coordenadas (x, y)
	private boolean parkedAtBase;
	private boolean available;

	// Constructor
	public vmp(int id, double[] location) {
		this.id = id;
		this.location = location;
		this.parkedAtBase = true;
		this.available = true;
	}

	//Obtener ID
	public int getId() {
		return id;
	}

	//Asignar ID
	public void setId(int id) {
		this.id = id;
	}

	//Obtener localización
	public double[] getLocation() {
		return location;
	}

	//Asignar localización
	public void setLocation(double[] location) {
		this.location = location;
	}

	//¿Aparcado en base?
	public boolean isParkedAtBase() {
		return parkedAtBase;
	}
	
	//Aparcar
	public void setParkedAtBase(boolean parkedAtBase) {
		this.parkedAtBase = parkedAtBase;
	}

	//¿Disponible?
	public boolean isAvailable() {
		return available;
	}

	//"liberar"
	public void setAvailable(boolean available) {
		this.available = available;
	}

	//Calcular la distancia al centro de la ciudad (punto (0, 0))
	public double distanceToCityCenter() {
		double x = location[0];
		double y = location[1];
		return Math.sqrt(x * x + y * y);
	}

	//Alquilar el vmp
	public void rentvmp() {
		setParkedAtBase(false);
		setAvailable(false);
	}

	//Devolver el vmp a la base
	public void returnvmp() {
		setParkedAtBase(true);
		setAvailable(true);
	}

	//Liberar el vmp en cualquier punto de la ciudad
	public void releasevmp() {
		setParkedAtBase(false);
		setAvailable(true);
	}

	// Bloquear el vmp
	public void lockvmp() {
		available = false;
	}
}

