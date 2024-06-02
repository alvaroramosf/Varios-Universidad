#!/bin/bash

echo "Introduzca el nombre de un directorio: "
read nom_dir

if test -d "$nom_dir"
then
	num_files=0
	num_dirs=0
	cd "$nom_dir"
	for i in *
	do
		if test -f "$i"
		then
			num_files=$((num_files+1))
		fi

		if test -d "$i"
		then
			num_dirs=$((num_dirs+1))
		fi
	done
	cd ..

	echo "El numero de ficheros y directorios en $nom_dir es de $num_files y $num_dirs, respectivamente"

else
	echo "$nom_dir no es un directorio"
fi
