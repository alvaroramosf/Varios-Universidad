#!/bin/bash

# Verificar si se proporcionaron los argumentos esperados
if [ "$#" -ne 0 ]; then
    echo "Uso: $0 < especificación" >&2
    exit 1
fi


while IFS=, read -r grupo_volumen volumen_logico tamagno tipo_fs punto_montaje || [ -n "$grupo_volumen" ]; do
    # Eliminar espacios
    tamagno=$(echo "$tamagno" | tr -d ' ')
    
    # Verificar si el volumen logico ya existe
    if lvs "$grupo_volumen/$volumen_logico" > /dev/null 2>&1; then
        # Extender el volumen logico
        if lvextend -L+"$tamagno" "$grupo_volumen/$volumen_logico"; then
            # Redimensionar el sistema de archivos
            if resize2fs "/dev/$grupo_volumen/$volumen_logico"; then
                echo "Volumen '$volumen_logico' en '$grupo_volumen' extendido."
            else
                echo "Error al redimensionar '$volumen_logico' en '$grupo_volumen'." >&2
            fi
        else
            echo "Error al extender '$volumen_logico' en '$grupo_volumen'." >&2
        fi
    else
        # Crear el volumen logico y el sistema de archivos
        if echo "y" | lvcreate -L "$tamagno" -n "$volumen_logico" "$grupo_volumen"; then
            if mkfs -t "$tipo_fs" "/dev/$grupo_volumen/$volumen_logico"; then
                echo "Volumen '$volumen_logico' en '$grupo_volumen' creado."

                # Agregar la entrada al archivo /etc/fstab
                echo "/dev/$grupo_volumen/$volumen_logico $punto_montaje $tipo_fs defaults 0 0" >> /etc/fstab
            else
                echo "Error al crear en '$volumen_logico' en '$grupo_volumen'." >&2
            fi
        else
            echo "Error al crear '$volumen_logico' en '$grupo_volumen'." >&2
        fi
    fi
done

exit 0
