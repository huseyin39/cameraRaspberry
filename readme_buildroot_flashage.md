Créer un système d'exploitation avec buildroot:
  installer docker (voir leur guide): https://docs.docker.com/install/linux/docker-ce/ubuntu/
  docker sert à compiler un OS pour la raspberry, on utilise une image précompilée car le temps de compilation est long
  
récupération de l'image pré-compilée:
$ docker pull pblottiere/embsys-rpi3-buildroot-video

Lancer le conteneur docker:
$ docker run -it pblottiere/embsys-rpi3-buildroot /bin/bash

se placer dans le dossier /root:
$ cd /root

il y a une image pré-compilée:
$ ls
buildroot-precompiled-2017.08.tar.gz

décompresser la tarball:
# tar zxvf buildroot-precompiled-2017.08.tar.gz
# cd buildroot-precompiled-2017.08

# make embsys_defconfig

ouvrir le menu de configuration:
# make menuconfig

Pour pouvoir utiliser la caméra depuis la raspberry, il faut 2 packages:
vérifier que l'option BR2_PACKAGE_RPI_FIRMWARE_X est activée, la rechercher avec la commande '/' dans buildroot, on doit avoir:
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
Idem pour l'option BR2_PACKAGE_LIBV4L
  
  
  
Maintenant il faut flasher la carte SD

###############################################################################################################
Pour avoir le support de la caméra sur la RPI3, un firmware spécifique doit être compilé avec Buildroot. Pour cela, il faut activer l'option BR2_PACKAGE_RPI_FIRMWARE_X dans le fichier de configuration de Buildroot.

De plus, afin d'intéragir avec la caméra, l'API de V4L est conseillée. Il est donc nécessaire d'activer l'option BR2_PACKAGE_LIBV4L dans le fichier de configuration Buildroot.

Votre système d'exploitation précompilé grâce à Buildroot est disponible via une image Docker (comme lors des TPs):

$ docker pull pblottiere/embsys-rpi3-buildroot-video

Pour créer un conteneur:

$ docker run -it pblottiere/embsys-rpi3-buildroot-video /bin/bash
docker# cd /root
docker# ls
buildroot-precompiled-2017.08.tar.gz
docker# tar zxvf buildroot-precompiled-2017.08.tar.gz

Le nécessaire pour flasher la carte RPI3 avec le support de la caméra est alors disponible:

    sdcard.img à flasher sur la carte SD avec la commande dd
    start_x.elf et fixup_x.dat à copier avec la commande cp sur la 1ère partition de la carte SD

Il faut finalement modifier le fichier config.txt de la 1ère partition de la carte SD pour ajouter:

start_x=1
gpu_mem=128
###############################################################################################################







































Cross compilation du code pour la raspberry
  (il faut cross compiler car le code doit tourner sur le processeur et la version de l'os installé sur la raspberry)
  
  
  
  
  
  
  
  
flashage de la carte ?????
  on insère la carte SD dans le lecteur du pc (mount)
   nécessaire pour flasher la carte RPI3 avec le support de la caméra est alors disponible:

    sdcard.img à flasher sur la carte SD avec la commande dd
    start_x.elf et fixup_x.dat à copier avec la commande cp sur la 1ère partition de la carte SD

Il faut finalement modifier le fichier config.txt de la 1ère partition de la carte SD pour ajouter:

