# cameraRaspberry

# Montage électronique:
La raspberry est alimenté via le 220V, le servo-moteur est branché sur un des GPIO disponible (le 17 pour nous) ainsi que sur la masse et le 5V. La communication entre la Raspberry et l'ordinateur s'effectue via les ports séries (Transmission-Receptions de la Raspberry). La console GTKTerm permet ensuite d'émuler un terminal avoir accès à la Raspberry. Enfin, la caméra se branche sur le port "camera" de la Raspberry.


# Serveur Python pour commander le servo-moteur: 

Le GPIO utilisé est le numéro 17 sur la Raspberry PI.
Le serveur du moteur écoute sur le port 20000. Cette écoute est bloquante tant qu'aucune connextion n'est entrée. Dès qu'un client se connecte, l'écoute de requête est mise en place, celle ci est également bloquante. Le client émet donc une requête.
Cette requête doit soit correspondre à 'end' pour mettre fin à la connection, soit correspondre à une commande. Cette commande doit être un entier entre 0 et 180 (due aux caractéristiques de la caméra). Dans le but de vérifier la conformité des requêtes, une méthode annexe (check_int()) a été mise en place.
Enfin, la méthode setAngle(angle) permet d'actionner la caméra en fonction de l'angle fourni.



# Serveur caméra et client:

Le client et le serveur choisissent le port (20000 pour le servo moteur) pour savoir à quel serveur se connecter. De plus, on entre l'ip du serveur chez le client pour se connecter. Pour terminer la session il suffit que le client envoie "end" au serveur.

Après la complitation du client en utilisant le gcc(ex: gcc -o nomDuFichier -Ficher.c), on utilise la commande ./nomDuFichier pour lancer le client. Pour le serveur de la camera on utilise la cross compilation et puis sur la raspberry on lance le serveur.

Le serveur fonctionne via TCP/IP également, on  va créer un socket (le port est spécifié au lancement du .exe) afin que le client et le serveur caméra puissent se connecter. Le serveur reste en statut bloquant jusqu’à ce qu'un client se connecte. Après s'être connecté, le client envoie le nom de l’image qui va être prise par la caméra, puis le serveur éxecute le code pour prendre la photo.

Le code exécuté est le code cross-compilé [v4l2grab.c](https://github.com/twam/v4l2grab/blob/master/v4l2grab.c).
