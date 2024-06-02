#!/bin/bash

# Comprobar datos
if [ $# -lt 2 ]; then
    echo "Usar: $0 <nombre_grupo_volumenes> <particion1> [<particion2> ...]"
    exit 1
fi

# Nombre del grupo
vg_name=$1
shift

# Desmontar particiones
for partition in "$@"; do
    # Si está montada, desmontar
    if mount | grep -q "$(df -P "$partition" | awk 'NR==2 {print $1}')"; then
        umount "$partition"
        echo "La partición $partition ha sido desmontada."
    fi
done

# Añadir particiones al grupo de volúmenes
for partition in "$@"; do
    # ¿Existe la partición?
    if [ ! -e "$partition" ]; then
        echo "La partición $partition no existe."
        exit 1
    fi

    # Crear un volumen físico
    pvcreate "$partition"

    # Extender el grupo
    vgextend "$vg_name" "$partition"
done

vgdisplay "$vg_name"
