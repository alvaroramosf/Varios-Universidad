#/bin/bash


for parametro in "$@"; do
	if [ -e "$parametro" ]; then
		more "$parametro"
	else
		echo "$parametro no es un fichero"
	fi
done

