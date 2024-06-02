

Parte 1
===========================================================
Primero, creamos el disco duro desde las utilidades de VB. Hemos usado un tamaño de 250MB y discos duros virtuales.

Instalamos el paquete para trabajar con volúmenes lógicos

sudo apt install lvm2

Dentro de la MV, usamos lsblk para saber que discos y particiones hay configuradas, y obtener el nombre del nuevo disco.

 lsblk
NAME   MAJ:MIN RM  SIZE RO TYPE MOUNTPOINT
sda      8:0    0   20G  0 disk 
├─sda1   8:1    0   19G  0 part /
├─sda2   8:2    0    1K  0 part 
└─sda5   8:5    0  975M  0 part [SWAP]
sdb      8:16   0  250M  0 disk 
sr0     11:0    1   51M  0 rom 

El nombre del nuevo disco es sdb.

Instalamos parted para poder usar la herramienta sudo apt install parted

Corremos parted sobre el disco con permisos de superusuario
sudo parted /dev/sdb

Creamos la tabla de particiones GUID
mklabel gpt

Creamos las particiones con mkpart

(parted) mkpart primary ext3 0% 50%
(parted) mkpart primary ext4 50% 100%

Number  Start   End    Size   File system  Name     Flags
 1      1049kB  131MB  130MB  ext3         primary
 2      131MB   261MB  130MB  ext4         primary

Desde Debian, creamos los sistemas de archivos:
sudo mkfs.ext3 /dev/sdb1
sudo mkfs.ext4 /dev/sdb2

Creamos las ubicaciones donde vamos a montar los discos y los montamos:
 mkdir sdb1ext3
 mkdir sdb2ext4

sudo mount /dev/sdb1 /home/as/sdb1ext3
sudo mount /dev/sdb2 /home/as/sdb2ext4

Comprobamos que los discos se han montado correctamente.

NAME   MAJ:MIN RM  SIZE RO TYPE MOUNTPOINT
sda      8:0    0   20G  0 disk 
├─sda1   8:1    0   19G  0 part /
├─sda2   8:2    0    1K  0 part 
└─sda5   8:5    0  975M  0 part [SWAP]
sdb      8:16   0  250M  0 disk 
├─sdb1   8:17   0  124M  0 part /home/as/sdb1ext3
└─sdb2   8:18   0  124M  0 part /home/as/sdb2ext4
sr0     11:0    1   51M  0 rom

Editamos /etc/fstab para que se monten en el arranque, añadimos estas dos líneas al final-

/dev/sdb1  /home/as/sdb1ext3 ext3  defaults  0  2
/dev/sdb2  /home/as/sdb2ext4 ext4  defaults  0  2

Reiniciamos

Parte 2
===========================================================
Resultado:
```
alberto@debian-alberto:~/ADSIS/practica_5$ ./practica5_parte2.sh 192.168.56.10
Discos duros disponibles y sus tamaños
/dev/sda:  20971520
/dev/sdb:    256000
total: 21227520 bloques
Particiones y sus tamaños
/dev/sda1  *          2048 39942143 39940096    19G 83 Linux
/dev/sda2         39944190 41940991  1996802   975M  5 Extendida
/dev/sda5         39944192 41940991  1996800   975M 82 Linux swap / Solaris
/dev/sdb1      2048 255999   253952   124M Sistema de ficheros de Linux
/dev/sdb2    256000 509951   253952   124M Sistema de ficheros de Linux
Informacion de montaje de sistemas de ficheros
S.ficheros     Tipo     Tamaño Usados  Disp Uso% Montado en
udev           devtmpfs   973M      0  973M   0% /dev
/dev/sda1      ext4        19G   1,5G   17G   9% /
/dev/sdb2      ext4       115M    14K  106M   1% /sdb2ext4
/dev/sdb1      ext3       115M    31K  109M   1% /sdb1ext3

```

Parte 3
===========================================================
Si queremos que arranque sin errores y partimos de la práctica anterior, el programa debería funcionar en la primera ejecución, pero al reiniciar la máquina tendríamos un problema por que el fichero /etc/fstab intentará montar unos discos que ya no existen. Para que esto no ocurra hay que comentar las lineas que montan estos discos.

Para ejecutar el programa otra vez, hay que volver a formatear los discos a ext4 para que dejen de estar en un grupo.

sudo mkfs.ext4 /dev/sda1
sudo mkfs.ext3 /dev/sda2

Para que no salgan warnings si hemos ejecutado los scripts anteriormente, indispensable en el ejercicio de los volumenes:
sudo vgreduce --removemissing vgadsis

Para borrar los grupos:
sudo umount /dev/vgadsis/vl1
sudo umount /dev/vgadsis/vl2
sudo umount /dev/vgadsis/vl3
sudo lvremove /dev/vgadsis/vl1
sudo lvremove /dev/vgadsis/vl2
sudo lvremove /dev/vgadsis/vl3

Procedimiento:

Creamos el disco con las utilidades de virtual box

Luego, ejecutamos lsblk para saber que disco es el nuevo:
NAME   MAJ:MIN RM   SIZE RO TYPE MOUNTPOINT
sda      8:0    0    20G  0 disk 
├─sda1   8:1    0    19G  0 part /
├─sda2   8:2    0     1K  0 part 
└─sda5   8:5    0   975M  0 part [SWAP]
sdb      8:16   0   250M  0 disk 
├─sdb1   8:17   0   124M  0 part /home/as/sdb1ext3
└─sdb2   8:18   0   124M  0 part /home/as/sdb2ext4
sdc      8:32   0 200,5M  0 disk 
sr0     11:0    1    51M  0 rom 

Particionamos con parted

 sudo parted /dev/sdc
GNU Parted 3.4
Using /dev/sdc
Welcome to GNU Parted! Type 'help' to view a list of commands.
(parted) mklabel gpt
(parted) mkpart primary ext3 0% 100%
(parted) set 1 lvm on
(parted) print
Model: ATA VBOX HARDDISK (scsi)
Disk /dev/sdc: 210MB
Sector size (logical/physical): 512B/512B
Partition Table: gpt
Disk Flags: 

Number  Start   End    Size   File system  Name     Flags
 1      1049kB  210MB  209MB  ext3         primary  lvm
(parted) quit

Desmmontamos y creamos el grupo que vamos a expandir.

sudo umount /dev/sdc1


 sudo pvcreate /dev/sdc1
WARNING: ext3 signature detected on /dev/sdc1 at offset 1080. Wipe it? [y/n]: y
  Wiping ext3 signature on /dev/sdc1.
  Physical volume "/dev/sdc1" successfully created.
  
  
 sudo vgcreate vgadsis /dev/sdc1
  Volume group "vgadsis" successfully created
  
  
 sudo lvcreate -n lvadsis -l 100% vgadsis
  Specified % is unknown.
  Invalid argument for --extents: 100%
  Error during parsing of command line.
  
  
 sudo lvcreate -n lvadsis -l 100%FREE vgadsis
  Logical volume "lvadsis" created.
  
  
 sudo mkfs.ext4 /dev/vgadsis/lvadsis 
mke2fs 1.46.2 (28-Feb-2021)
Creating filesystem with 200704 1k blocks and 50200 inodes
Filesystem UUID: 9bc44adb-0466-4d84-b3ab-f43fe92dc5a1
Superblock backups stored on blocks: 
	8193, 24577, 40961, 57345, 73729

Allocating group tables: done
Writing inode tables: done 
Creating journal (4096 blocks): done
Writing superblocks and filesystem accounting information: done 

Creamos el directorio
 mkdir sbclvm

Montamos
sudo mount /dev/vgadsis/lvadsis /home/as/sbclvm

El script se ejecuta con sudo.

Resultado:
```
 sudo ./practica5_parte3_vg.sh vgadsis /dev/sdb1 /dev/sdb2
La partición /dev/sdb1 ha sido desmontada.
La partición /dev/sdb2 ha sido desmontada.
WARNING: ext3 signature detected on /dev/sdb1 at offset 1080. Wipe it? [y/n]: y
  Wiping ext3 signature on /dev/sdb1.
  Physical volume "/dev/sdb1" successfully created.
  Volume group "vgadsis" successfully extended
WARNING: ext4 signature detected on /dev/sdb2 at offset 1080. Wipe it? [y/n]: y
  Wiping ext4 signature on /dev/sdb2.
  Physical volume "/dev/sdb2" successfully created.
  Volume group "vgadsis" successfully extended
  --- Volume group ---
  VG Name               vgadsis
  System ID
  Format                lvm2
  Metadata Areas        3
  Metadata Sequence No  4
  VG Access             read/write
  VG Status             resizable
  MAX LV                0
  Cur LV                1
  Open LV               0
  Max PV                0
  Cur PV                3
  Act PV                3
  VG Size               436,00 MiB
  PE Size               4,00 MiB
  Total PE              109
  Alloc PE / Size       49 / 196,00 MiB
  Free  PE / Size       60 / 240,00 MiB
  VG UUID               HAnR7F-wtwA-lKAx-O1g1-wuxE-NzrR-Dq3VpJ
```

 ./practica5_parte3_lv.sh
 
Fichero con datos:
```
vgadsis,vl1,100,ext3,/home/as/vl1
vgadsis,vl2,100,ext3,/home/as/vl2
vgadsis,vl3,100,ext3,/home/as/vl3
```

Ejecucion:
sudo ./practica5_parte3_lv.sh < practica5_parte3_ls_prueba

Resultado:

```
 sudo ./practica5_parte3_lv.sh < practica5_parte3_ls_prueba
WARNING: ext3 signature detected on /dev/vgadsis/vl1 at offset 1080. Wipe it? [y/n]:   Wiping ext3 signature on /dev/vgadsis/vl1.
  Logical volume "vl1" created.
mke2fs 1.46.2 (28-Feb-2021)
Creating filesystem with 102400 1k blocks and 25688 inodes
Filesystem UUID: 00dd2924-3dea-429c-b589-4291eb67c06b
Superblock backups stored on blocks: 
	8193, 24577, 40961, 57345, 73729

Allocating group tables: done                            
Writing inode tables: done                            
Creating journal (4096 blocks): done
Writing superblocks and filesystem accounting information: done 

Volumen lógico 'vl1' en 'vgadsis' creado.
Entrada agregada al archivo /etc/fstab para 'vl1' en 'vgadsis'.
WARNING: ext3 signature detected on /dev/vgadsis/vl2 at offset 1080. Wipe it? [y/n]:   Wiping ext3 signature on /dev/vgadsis/vl2.
  Logical volume "vl2" created.
mke2fs 1.46.2 (28-Feb-2021)
Creating filesystem with 102400 1k blocks and 25688 inodes
Filesystem UUID: 79afc052-740f-4f7b-a991-9954203a0baf
Superblock backups stored on blocks: 
	8193, 24577, 40961, 57345, 73729

Allocating group tables: done
Writing inode tables: done
Creating journal (4096 blocks): done
Writing superblocks and filesystem accounting information: done 

Volumen lógico 'vl2' en 'vgadsis' creado.
Entrada agregada al archivo /etc/fstab para 'vl2' en 'vgadsis'.
WARNING: ext3 signature detected on /dev/vgadsis/vl3 at offset 1080. Wipe it? [y/n]:   Wiping ext3 signature on /dev/vgadsis/vl3.
  Logical volume "vl3" created.
mke2fs 1.46.2 (28-Feb-2021)
Creating filesystem with 102400 1k blocks and 25688 inodes
Filesystem UUID: 06688f15-3042-4f16-b06c-1d47b9b255f2
Superblock backups stored on blocks: 
	8193, 24577, 40961, 57345, 73729

Allocating group tables: done                            
Writing inode tables: done                            
Creating journal (4096 blocks): done
Writing superblocks and filesystem accounting information: done 

Volumen lógico 'vl3' en 'vgadsis' creado.
Entrada agregada al archivo /etc/fstab para 'vl3' en 'vgadsis'.
```








