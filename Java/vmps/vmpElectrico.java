public class vmpElectrico extends vmp {
	private int carga;
	private boolean estaCargando;

	public vmpElectrico(int id, double[] location, int carga) {
		super(id, location);
		this.carga = carga;
		this.estaCargando = false;
	}
	
	//Porcentaje de bateria
	public int getPorcentajeBateria() {
		return this.carga;
	}
	
	//Alquilar el vmp
	@Override
	public void rentvmp() {
		setParkedAtBase(false);
		setAvailable(false);
		estaCargando = false;
	}

	//Devolver el vmp a la base
	@Override
	public void returnvmp() {
		setParkedAtBase(true);
		setAvailable(true);
		estaCargando = true;
	}
	
}
