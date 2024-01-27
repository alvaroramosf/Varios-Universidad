# Análisis coste de algoritmos

*(Copiado del pdf de las prácticas)*  

## Práctica 3.

El objetivo principal de la práctica es resolver un problema mediante dos estrategias diferentes: 

- a) Fuerza Bruta;
- b) Divide y Vencerás

En esta práctica se propone diseñar algoritmos para resolver el problema del mçaximo
solape entre intervalos. Dado un conjunto de intervalos definidos en los reales, calcular
el máximo solape consiste en encontrar la pareja de intervalos cuyo solape entre s´ı es
máximo. Por ejemplo, en el conjunto de intervalos [4.0, 7.5], [3.0, 5.0], [0.5, 2.5], [1.5, 8.0],
[0.0, 1.5], [2.0, 4.0], [1.0, 6.0], [3.5, 7.0], que se representan gr´aficamente en la Figura 1, el
máximo solape es el de los intervalos [1.0, 6.0] y [1.5, 8.0] que es igual a 4.5.

## Práctica 4

Ejecutar las estrategias de Fuerza Bruta y de Divide y Vencer´as para conjuntos
de entre 100 y 4000 intervalos generados de forma aleatoria (el valor mínimo para
el extremo izquierdo del intervalo es minini y el valor m´aximo para el extremo
derecho maxfin, ver maxsolape.hpp).
Generar gráficas que muestren el tiempo de ejecución en función del número de
intervalos para cada una de las estrategias. Las gráficas se pueden realizar guardando las datos que se quieren mostrar en un fichero de texto y después haciendo
una llamada al sistema desde el programa