
# Practica 4
### Diagrama de red:
Lo primero que hemos hecho ha sido hacer un diagrama de red con las interfaces conectadas, y sus direcciones MAC e IP, para saber como escribir los ficheros de configuración de las máquinas virtuales.


MV		Nº INTERFAZ	IP		MAC		TARJETA RED	
1		0		127.0.0.1	000000000000	lo (loopback)
1		1		RED NAT		0800272E3967	enp0s1
1		2		192.168.56.11	080027A67FB2	enp0s8	
2		0		127.0.0.1	000000000000	lo (loopback)
2		1		RED NAT		0800272E3967	
2		2		192.168.56.12	0800272E3967	
HOST				192.168.56.1

Hemos modificado el archivo /etc/network/interfaces de ambas maquinas virtuales para que la conexión se realice en el arranque.

Host 1:

```
# This file describes the network interfaces available on your system
# and how to activate them. For more information, see interfaces(5).

source /etc/network/interfaces.d/*

# The loopback network interface
auto lo
iface lo inet loopback

# The primary network interface
allow-hotplug enp0s3
iface enp0s3 inet dhcp

# Interfaz 2
auto enp0s8
iface enp0s8 inet static
	address 192.168.56.11
	netmask 255.255.255.0
```

Host 2:

```
# This file describes the network interfaces available on your system
# and how to activate them. For more information, see interfaces(5).

source /etc/network/interfaces.d/*

# The loopback network interface
auto lo
iface lo inet loopback

# The primary network interface
allow-hotplug enp0s3
iface enp0s3 inet dhcp

# Interfaz 2
auto enp0s8
iface enp0s8 inet static
	address 192.168.56.12
	netmask 255.255.255.0
```

Hemos modificado el fichero "/etc/ssh/sshd_config" en ambas máquinas para que el usuario root no se pueda conectar por SSH, y permitir la autentificación con claves. Para ello, hemos descomentado estas lineas.

```

PermitRootLogin no

PubkeyAuthentication yes

```

A continuación, hemos corrido las dos máquinas virtuales a la vez y les hemos hecho ping desde el host para comprobar que la conexión existe.

Para configurar el ssh hemos ejecutado este comando en nuestro host.

```
ssh-keygen -t ed25519 -f ~/.ssh/id_as_ed25519
```

El comando nos ha devuelto

```
rufus@wax:~$ ssh-keygen -t ed25519 -f ~/.ssh/id_as_ed25519
Generating public/private ed25519 key pair.
Enter passphrase (empty for no passphrase): 
Enter same passphrase again: 
Your identification has been saved in /home/rufus/.ssh/id_as_ed25519
Your public key has been saved in /home/rufus/.ssh/id_as_ed25519.pub
The key fingerprint is:
SHA256:yVg9AYJ7UVnh2RA5AGaiW32rO9opY++ftGiY8LT5rzE rufus@wax
The key's randomart image is:
+--[ED25519 256]--+
|    ..=o+=*+     |
|   ..=...oo=     |
|  . ....o =..    |
|   o. .= o .     |
|  .  .. S        |
|  . .  .         |
|   + =E .        |
|    X.oB o       |
|   ..OX==        |
+----[SHA256]-----+
```
Luego, hemos ejecutado este comando en el host para cada una de las dos maquinas virtuales, para que el servidor tenga nuestra clave publica.
```
ssh-copy-id -i ~/.ssh/id_as_ed25519.pub as@192.168.56.11

ssh-copy-id -i ~/.ssh/id_as_ed25519.pub as@192.168.56.12
```

Luego hemos reiniciado el servicio de ssh en cada una de las máquinas virtuales:

```
sudo systemctl restart sshd

```
Es importante también ejecutar este comando para asegurarse de que las claves tengan los permisos adecuados.
```
chmod 600 ~/.ssh/id_as_ed25519
```
Para conectarnos desde el host, hemos usado ssh de forma normal.
```
ssh as@192.168.56.11

ssh as@192.168.56.12
```

Además, para poder usar sudo en nuestro script, es necesario añadir esta línea en el fichero de configuración de el programa sudo:
```
as ALL=(ALL) NOPASSWD: ALL
```




