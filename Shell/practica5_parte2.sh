#!/bin/bash

user="as"
dir_ip=$1
key_file="~/.ssh/id_as_p5"

if ping $dir_ip -c 1 > /dev/null
then
	echo "Discos duros disponibles y sus tamaños"
	ssh -i $key_file $user@$dir_ip sudo sfdisk -s
	echo "Particiones y sus tamaños"
	ssh -i $key_file $user@$dir_ip sudo sfdisk -l | grep "^[!^/]"
	echo "Informacion de montaje de sistemas de ficheros"
	ssh -i $key_file $user@$dir_ip sudo df -hT | grep -v '^tmpfs*'
else
	echo "Error de conexion"
fi
