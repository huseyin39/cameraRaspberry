#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h> 

int main()
{ int st;
  int fic,ficopen=0,ficres;
  int end = 0;
  int portserver;
  int s;
  struct sockaddr_in server;
  struct sockaddr name;
  char * adrserver;
  char mes[1024];

  adrserver = (char *) malloc(32);
 
  printf("TCP client program\n");
  
  
  do {


// pour se connecter on server on a besoin de l'ip, dans cette partie on obtient l'adresse ip


    printf("enter the IP address of the server in the format: a.b.c.d :\n");
    scanf("%s",adrserver);
    if (inet_aton(adrserver, &server.sin_addr)!=0) 
      end=2;
    else 
      //si l'adresse n'est pas entree en bon format un message d'erreur vas s'afficher
      printf("invalid address\n");
   } while (end==0);


//maintenant on choisit le port du serveur

      printf("Enter the port number of server:\n");
      scanf("%d",&portserver);
      printf("Appel fonction socket\n");
//creation du socket
      s = socket (AF_INET,SOCK_STREAM,6);
      if (s==-1) {
           printf("invalid socket\n");
           return -1;
         }
      printf ("connexion request \n");
      server.sin_family = AF_INET;
      server.sin_port = htons(portserver);
// etablir la connection
      st = connect(s,(const struct sockaddr *)&server,sizeof(server));
      if (st!=0) {
           printf("Connexion rejected \n");
           return -1;
         }
      printf("Connexion established; \n");
// menu pour choisir changement de postion de camera ou prendre une photo ou quitter

      printf("*****************System Embarque******************* \n");
      printf("\n \n \n");
     do
	{
        printf("entree l'angle pour le moteur :\n");
        scanf("%s",mes);
// envoyer le message
          st = send(s,mes,strlen(mes),0);
		if(strcmp(mes,"end")!=0)
          {
          if (st!=strlen(mes)) 
            printf("error occur when sending the message\n");
          else {
//recevoir le message du serveur 
              st = recv(s,&mes,sizeof(mes),0);
              printf("%s \n",mes);
              }
}
    }while (strcmp(mes,"end")!=0);
 }
