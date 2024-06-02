//Autor: Álvaro Ramos Fustero ~ 855798

public class Main {
	public static void main(String[] args) {
		for (int i = 1; i <= 3; i++) {
			System.out.println("PROGRAMA " + i);
			Programa programa = new Programa(i);
			programa.listarPrograma();
			System.out.println();
			programa.ejecutarPrograma();
			System.out.println();
		}
	}
}

