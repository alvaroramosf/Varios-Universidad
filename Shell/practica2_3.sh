#!/bin/bash

if [ $# -eq 1 ]
then
	if test -f "$1"
	then
		chmod u+x "$1"
		chmod g+x "$1"
		stat "$1" --format=%A
	else
		echo "$1 no existe"
	fi
else
	echo "Sintaxis: practica2_3.sh <nombre_archivo>"
fi
