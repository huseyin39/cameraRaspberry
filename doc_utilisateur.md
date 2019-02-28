server camera et client

le serveur camera utilise le TCP/IP pour se connecter avec le client. le client et le serveur choisissent le port (20000 pour le servo moteur) 
pour savoir à quel serveur se connecter. en plus on entre l'ip du serveur chez le client pour se connecter. pour terminer la session 
il suffit que le client envoie "end" au serveur.

après la complitation du client en utilisant le gcc(ex: gcc -o nomDuFichier -Ficher.c), on utilise la commande ./nomDuFichier pour lancer le client. 
pour le serveur de la camera on utilise la cross compilation et puis sur la raspberry on lance le serveur.
