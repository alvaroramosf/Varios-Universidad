#!/bin/bash

echo -n "Introduzca una tecla:"
read -n 1 caracter
echo

if [[ "$caracter" =~ ^[0-9]+$ ]]; then
	echo "$caracter es un numero"
elif [[ "$caracter" =~ [[:alpha:]] ]]; then
	echo "$caracter es una letra"
else
	echo "$caracter es caracter especial"
fi

