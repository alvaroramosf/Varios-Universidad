#!/bin/bash

echo -n "Introduzca el nombre del fichero: "
read fichero

if test -f "$fichero"
then
	echo -n "Los permisos del archivo $fichero son: "
	if test -r "$fichero"
	then
		echo -n "r"
	else
		echo -n "-"
	fi
	if test -w "$fichero"
	then
		echo -n "w"
	else
		echo -n "-"
	fi
	if test -x "$fichero"
	then
		echo -n "x"
	else
		echo -n "-"
	fi

	echo ''
else
	echo "$fichero no existe"
fi
