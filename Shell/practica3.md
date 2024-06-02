# Memoria práctica 3

A la hora de realizar esta práctica, lo primero que hicimos fue realizar un texto con las distintas
especificaciones que se nos piden en el enunciado, ordenadas y una extructura general del programa.
En un principio, teníamos demasiados if anidados dentro de otros, por que habíamos realizado el manejo
de errores de esa manera. Más adelante nuestro tutor de prácticas nos dijo que para manejar los errores
se solían implementar funciones al principio, así que lo implementamos como se nos dijo, mediante las funciones:

```
if [ $(whoami) != "root" ]; then
	echo "Este script necesita privilegios de administracion"
	exit 1
fi

if [ $# -ne 2 ]; then
	echo "Numero incorrecto de parametros"
 	exit
fi
```
Respecto al resto de decisiones de diseño se encuentran comentadas en el código, ya que no las hemos considerado tan relevantes
El resto del trabajo fue bastante sencillo y no tuvimos más problemas, simplemente fuimos rellenando 
en la estructura que habíamos hecho con el código que ibamos programando. A la hora de pasarles los
 tests, no nos funcionaron a la primera, pero pudimos solventar los errores con un poco de trabajo.


