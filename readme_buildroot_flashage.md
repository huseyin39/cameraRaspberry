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

vérifier que 





Cross compilation du code pour la raspberry
  (il faut cross compiler car le code doit tourner sur le processeur et la version de l'os installé sur la raspberry)
  
  
  
  
  
  
  
  
flashage de la carte ?????
  on insère la carte SD dans le lecteur du pc (mount)
   nécessaire pour flasher la carte RPI3 avec le support de la caméra est alors disponible:

    sdcard.img à flasher sur la carte SD avec la commande dd
    start_x.elf et fixup_x.dat à copier avec la commande cp sur la 1ère partition de la carte SD

Il faut finalement modifier le fichier config.txt de la 1ère partition de la carte SD pour ajouter:

