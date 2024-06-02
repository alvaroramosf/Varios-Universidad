#!/bin/bash

if [ $# -ne 3 ]; then
	echo "Numero incorrecto de parametros"
 	exit
fi


if [ $1 = "-a" ]; then
	while read ip
	do	
		#comprueba si se puede conectar al ssh
		ssh -ni ~/.ssh/id_as_ed25519 as@$ip true 2>/dev/null
		if [ $? -ne 0 ]; then
			echo "$ip no es accesible"
 			continue
		fi
	  	OldIFS=$IFS
		IFS=,
		while read login pass name ignore
		do
		
	    	if [ -z "$login" ] || [ -z "$pass" ] || [ -z "$name" ] || [ "$ignore" != "" ] ; then #comprobar que los 3 campos son distintos de la cadena vacía y que no hay mas de 3 campos
			echo "Campo invalido"
			continue
		fi
		
	    	if ssh -ni ~/.ssh/id_as_ed25519 as@$ip id "$login" &>/dev/null; then #comprobar si usuario ya existe, decir "El usuario <identificador> ya existe"
	      		echo "El usuario $login ya existe"
	   	else
			uid_actual=$(ssh -ni ~/.ssh/id_as_ed25519 as@$ip 'awk -F":" "\$3 >= 1815 {print \$3}" /etc/passwd' | sort -n | tail -1) #Busca los uids existentes y obtiene el mayor uid existente
			
			if [ -z "$uid_actual" ]; then #Si no se han encontrado UIDs mayores o iguales que 1815 uid_actual está vacío, entonces asigna el 1815
				nuevo_uid=1815
			else
				nuevo_uid=$((uid_actual + 1)) #Si hay uids mayores que 1815, añade el último disponible
			fi
			
			#Busca si el grupo con el nombre del usuario ya existe
			if [ -z $(ssh -ni ~/.ssh/id_as_ed25519 as@$ip 'awk -F: -v v="$login" '\''{if ($1==v) print $1}'\'' /etc/group') ] ; then
				ssh -ni ~/.ssh/id_as_ed25519 as@$ip sudo useradd -m -s /bin/bash -k /etc/skel -U -c "$name" -K UID_MIN=1815 -u "$nuevo_uid" "$login" #Si no existe lo crea y se une
			else
				ssh -ni ~/.ssh/id_as_ed25519 as@$ip sudo useradd -m -s /bin/bash -k /etc/skel -g "$login" -c "$name" -K UID_MIN=1815 -u "$nuevo_uid" "$login" #Si ya existe se une a el
			fi
			
			echo "$login:$pass" | ssh -ni ~/.ssh/id_as_ed25519 as@$ip sudo chpasswd
			ssh -ni ~/.ssh/id_as_ed25519 as@$ip sudo usermod -aG "$login" "$login"
			echo "$name ha sido creado"
			continue
	    	fi
		done < "$2"
		IFS=$OldIFS
	done < "$3"
	exit
elif [ $1 = "-s" ]; then
	while read ip
	do	
		#comprueba si se puede conectar al ssh
		ssh -ni ~/.ssh/id_as_ed25519 as@$ip true 2>/dev/null
		if [ $? -ne 0 ]; then
			echo "$ip no es accesible"
 			continue
		fi
		ssh -ni ~/.ssh/id_as_ed25519 as@$ip sudo mkdir -p /extra #crear el directorio /extra/backup aunque no se borre ningún usuario.
		ssh -ni ~/.ssh/id_as_ed25519 as@$ip sudo mkdir -p /extra/backup
		OldIFS=$IFS
	  	IFS=,
	 	while read user ignore
	  	do  		
	    		if ssh -ni ~/.ssh/id_as_ed25519 as@$ip id $login &> /dev/null; then #comprobar si usuario existe, si existe lo borra.
				user_home=$(ssh -ni ~/.ssh/id_as_ed25519 as@$ip "awk -F: -v v=\"$user\" '{if (\$1==v) print \$6}' /etc/passwd") #obtiene el directorio home del usuario
				if ssh -ni ~/.ssh/id_as_ed25519 as@$ip sudo tar fcz /extra/backup/$user.tar --absolute-names $user_home 2>/dev/null ; then   #hace backup del directorio home de cada usuario
					#si la backup se ha realizado sin problemas, borramos el usuario
					ssh -ni ~/.ssh/id_as_ed25519 as@$ip sudo userdel $user
					# borra también el directorio home de cada usuario.
					ssh -ni ~/.ssh/id_as_ed25519 as@$ip sudo rm -r $user_home
				fi
	    		fi
	  	done < "$2"
	  	IFS=$OldIFS
	done < "$3"
	exit
else
  	echo "Opcion invalida" 1>&2
  	exit
fi
