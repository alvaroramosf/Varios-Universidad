#!/bin/bash

if [ $(whoami) != "root" ]; then
	echo "Este script necesita privilegios de administracion"
	exit 1
fi

if [ $# -ne 2 ]; then
	echo "Numero incorrecto de parametros"
 	exit
fi

if [ $1 = "-a" ]; then
  	OldIFS=$IFS
	IFS=,
	while read login pass name ignore
	do
	
    	if [ -z "$login" ] || [ -z "$pass" ] || [ -z "$name" ] || [ "$ignore" != "" ] ; then #comprobar que los 3 campos son distintos de la cadena vacía y que no hay mas de 3 campos
		echo "Campo invalido"
		exit
	fi
	
    	if id "$login" &>/dev/null; then #comprobar si usuario ya existe, decir "El usuario <identificador> ya existe"
      		echo "El usuario $login ya existe"
   	else
		uid_actual=$(awk -F':' '$3 >= 1815 {print $3}' /etc/passwd | sort -n | tail -1) #Busca los uids existentes y obtiene el mayor uid existente
		
		if [ -z "$uid_actual" ]; then #Si no se han encontrado UIDs mayores o iguales que 1815 uid_actual está vacío, entonces asigna el 1815
			nuevo_uid=1815
		else
			nuevo_uid=$((uid_actual + 1)) #Si hay uids mayores que 1815, añade el último disponible
		fi
		
		#Busca si el grupo con el nombre del usuario ya existe
		if [ -z $(awk -F: -v v="$login" '{if ($1==v) print $1}' /etc/group) ] ; then
			useradd -m -s /bin/bash -k /etc/skel -U -c "$name" -K UID_MIN=1815 -u "$nuevo_uid" "$login" #Si no existe lo crea y se une
		else
			useradd -m -s /bin/bash -k /etc/skel -g "$login" -c "$name" -K UID_MIN=1815 -u "$nuevo_uid" "$login" #Si ya existe se une a el
		fi
		
		echo "$login:$pass" | chpasswd
		usermod -aG "$login" "$login"
		echo "$name ha sido creado"
    	fi
	done < "$2"
	IFS=$OldIFS
elif [ $1 = "-s" ]; then
	mkdir -p /extra #crear el directorio /extra/backup aunque no se borre ningún usuario.
	mkdir -p /extra/backup
	OldIFS=$IFS
  	IFS=,
 	while read user ignore
  	do  		
    		if id $login &> /dev/null; then #comprobar si usuario existe, si existe lo borra.
			user_home=$(awk -F: -v v="$user" '{if ($1==v) print $6}' /etc/passwd) #obtiene el directorio home del usuario
			if tar fcz /extra/backup/$user.tar --absolute-names $user_home 2>/dev/null ; then   #hace backup del directorio home de cada usuario
				#si la backup se ha realizado sin problemas, borramos el usuario
				userdel $user
				# borra también el directorio home de cada usuario.
				rm -r $user_home
			fi
    		fi
  	done < "$2"
  	IFS=$OldIFS
else
  	echo "Opcion invalida" 1>&2
  	exit
fi
