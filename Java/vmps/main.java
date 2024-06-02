//Autor: Álvaro Ramos Fustero ~ 855798

public class main {
	public static void main(String[] args) {

	vmp bicicleta1 = new vmp(1, new double[]{3.0, 4.0});
	vmp patinete1 = new vmpElectrico(2, new double[]{5.0, 6.0}, 50);
	vmp patinete2 = new vmpElectrico(4, new double[]{5.0, 6.0}, 50);
	vmp bicicleta2 = new vmp(3, new double[]{7.0, 8.0});

	flota flota = new flota();
	flota.agregarvmp(bicicleta1);
	flota.agregarvmp(patinete1);
	flota.agregarvmp(bicicleta2);
	flota.agregarvmp(patinete2);


	vmp vehiculoMasAlejado = flota.obtenerVehiculoMasAlejado();
	System.out.println("Vehiculo mas alejado del centro :" + vehiculoMasAlejado.getId());

	double radioLimite = 5.0;
	System.out.println("Vehiculos abandonados fuera de un radio de " + radioLimite);
	for (vmp vmp : flota.obtenerVehiculosAbandonados(radioLimite)) {
		System.out.println("ID: " + vmp.getId());
	}

	patinete2.releasevmp();


	double porcentajeBateriaLimite = 80;
	System.out.println("Vehiculos electricos con porcentaje de batería inferior a " + porcentajeBateriaLimite);
	for (vmpElectrico vmpElectrico : flota.obtenerVehiculosBateriaBaja(porcentajeBateriaLimite)) {
            System.out.println("ID:" + vmpElectrico.getId());
	}
    }
}

