## étape 1: installer docker
voir le guide à l'adresse: https://docs.docker.com/install/linux/docker-ce/ubuntu/
docker sert à compiler un OS pour la raspberry, on utilise une image précompilée car le temps de compilation est long

## étape 2: préparer le conteneur docker
récupération de l'image pré-compilée (évite de passer plusieurs heures a compiler tous l'OS)
````
$ docker pull pblottiere/embsys-rpi3-buildroot-video
````

Lancer le conteneur docker:
$ docker run -it pblottiere/embsys-rpi3-buildroot /bin/bash

se placer dans le dossier /root:
$ cd /root

il y a une image pré-compilée:
$ ls
buildroot-precompiled-2017.08.tar.gz

décompresser la tarball:
````
# tar zxvf buildroot-precompiled-2017.08.tar.gz
# cd buildroot-precompiled-2017.08
````
définir les options de compilation:
````
# make embsys_defconfig
````

ouvrir le menu de configuration:
````
# make menuconfig
````

Pour pouvoir utiliser la caméra depuis la raspberry, il faut 2 packages:
vérifier que l'option BR2_PACKAGE_RPI_FIRMWARE_X est activée, la rechercher avec la commande '/' dans buildroot. On doit avoir:
  │ Symbol: BR2_PACKAGE_RPI_FIRMWARE_X [=y]   
  │ Type  : boolean   
  │ Prompt: extended ('x', more codecs)    
  │   Location:                     
  │     -> Target packages           
  │       -> Hardware handling       
  │         -> Firmware            
  │           -> rpi-firmware (BR2_PACKAGE_RPI_FIRMWARE [=y])   
  │ (1)         -> Firmware to boot (<choice> [=y])    
  │   Defined at package/rpi-firmware/Config.in:28 
  │   Depends on: <choice> 
l'option BR2_PACKAGE_LIBV4L doit également être activée
  
  
  
## étape 3: flasher la carte SD

1-trouver le container id du docker dans lequel se trouve l'image a flasher
ouvrir un terminal et taper $ sudo docker ps
lire le champ CONTAINER ID, par exemple 7a7b1409293b

2-copier l'image du conteneur docker sur le PC (car l'image est dans le conteneur qui n'a pas accès a la carte sd montée sur le pc)
````
$ docker cp <container_id>:/root/buildroot-precompiled-2017.08/output/images/sdcard.img .
````

3-trouver le path de la carte sd dans /dev avec la commande dmesg

4-flasher cette image sur la carte
````
$ sudo dd if=sdcard.img of=/dev/sdX
````

5-copier startup_x.elf et fixup_x.dat sur la 1ère partition de la carte SD avec la commande cp

6-modifier le fichier config.txt de la 1ère partition de la carte SD pour ajouter:
start_x=1
gpu_mem=128


## étape 4: cross-compilation
Il faut cross-compiler car le code doit tourner sur le processeur et la version de l'os installé sur la raspberry. La cross compilation se fait depuis le conteneur docker que l'on a créé.

1-Il faut d'abord copier le code a cross-compiler depuis la machine hote vers le conteneur docker avec la commande cp
````
$ sudo docker cp code.c 7a7b1409293b:/code.c
````

2-cross compiler en utilisant le programme gcc correspond à l'architecture de la raspberry:
````
# ./output/host/usr/bin/arm-linux-gcc code.c -o executable

````

3-copier le code compilé sur le pc hote
````
$ sudo docker cp 7a7b1409293b:/executable .
````

4-puis le copier dans le répertoire /home/usr de la 2ième partition de la carte SD


Au démarrage de la raspberry, il faut lancer bcm2835-v4l2 grâce à la commande modprobe (on se connecte à la raspberry avec gtkterm en USB pour ouvrir une console a distance permettant de lancer cette commande)
cela devrait permettre de voir video0 dans /dev (faire: $ rpi3# ls /dev/video0)

La raspberry est prête à être utiliser, voir la doc utilisateur doc_utilisateur.md
