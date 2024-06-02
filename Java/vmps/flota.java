//Autor: Álvaro Ramos Fustero ~ 855798

import java.util.ArrayList;
import java.util.List;

public class flota {
	private List<vmp> vehiculos;

	// Constructor
	public flota() {
		this.vehiculos = new ArrayList<>();
	}

	public void agregarvmp(vmp vmp) {
		vehiculos.add(vmp);
	}

	// Método para obtener el vehículo más alejado del centro
	public vmp obtenerVehiculoMasAlejado() {
		vmp vehiculoMasAlejado = null;
		double maxDistancia = Double.MIN_VALUE;
		for (vmp vmp : vehiculos) {
			double distancia = vmp.distanceToCityCenter();
			if (distancia > maxDistancia) {
				maxDistancia = distancia;
				vehiculoMasAlejado = vmp;
			}
		}
		return vehiculoMasAlejado;
	}

	// Método para obtener los vehículos abandonadoS
	public List<vmp> obtenerVehiculosAbandonados(double radio) {
		List<vmp> vehiculosAbandonados = new ArrayList<>();
		for (vmp vmp : vehiculos) {
			if (!vmp.isParkedAtBase() && vmp.distanceToCityCenter() > radio) {				
				vehiculosAbandonados.add(vmp);
				vmp.lockvmp(); // Bloquear el vmp
			}
		}
		return vehiculosAbandonados;
	}

	// Método para obtener los vehículos eléctricos con poca bateria
	public List<vmpElectrico> obtenerVehiculosBateriaBaja(double porcentajeBateria) {
		List<vmpElectrico> vehiculosConBateriaBaja = new ArrayList<>();
		for (vmp vehiculo : vehiculos) {
			if (vehiculo instanceof vmpElectrico) {
				vmpElectrico vmpElectrico = (vmpElectrico) vehiculo;
				if (!vmpElectrico.isParkedAtBase() && vmpElectrico.isAvailable() && vmpElectrico.getPorcentajeBateria() < porcentajeBateria) {
					vehiculosConBateriaBaja.add(vmpElectrico);
				}
			}
		}
	return vehiculosConBateriaBaja;
	}
}
/* Método para calcular el porcentaje de vehículos en uso de tipo patinete frente al total en uso:
*
* No entiendo muy bien a que se refiere esta parte del ejercicio. ¿Tengo que crear una clase aparte de patinete? ¿Hay patinetes no eléctricos?
*/

