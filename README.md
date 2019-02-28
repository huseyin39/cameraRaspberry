# cameraRaspberry

# Montage électronique:
La raspberry est alimenté via le 220V, le servo-moteur est branché sur un des GPIO disponible (le 17 pour nous) ainsi que sur la masse et le 5V. La communication entre la Raspberry et l'ordinateur s'effectue via les ports séries (Transmission-Receptions de la Raspberry). La console GTKTerm permet ensuite d'émuler un terminal avoir accès à la Raspberry. Enfin, la caméra se branche sur le port "camera" de la Raspberry.


# Serveur Python pour commander le servo-moteur: 

Le GPIO utilisé est le numéro 17 sur la Raspberry PI.
Le serveur du moteur écoute sur le port 20000. Cette écoute est bloquante tant qu'aucune connextion n'est entrée. Dès qu'un client se connecte, l'écoute de requête est mise en place, celle ci est également bloquante. Le client émet donc une requête.
Cette requête doit soit correspondre à 'end' pour mettre fin à la connection, soit correspondre à une commande. Cette commande doit être un entier entre 0 et 180 (due aux caractéristiques de la caméra). Dans le but de vérifier la conformité des requêtes, une méthode annexe (check_int()) a été mise en place.
Enfin, la méthode setAngle(angle) permet d'actionner la caméra en fonction de l'angle fourni.
