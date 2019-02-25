#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h> 
int main(int argc, char ** argv)
{ 
int st,fic,res;
int portserver;
unsigned int lgclient;
int s,soc;
struct sockaddr_in server,client;
char mes[1024];
  
  printf("File Server\n");
  if (argc<2) {
     printf("you should enter a port number\n");
     return -1;
   }
  sscanf(argv[1],"%d",&portserver);
  soc = socket (AF_INET,SOCK_STREAM,6); // socket creation
  if (soc==-1) {
    printf("Retour socket invalide");
    return (-1);
  }
  // declare the IP address and port number of server
  server.sin_family = AF_INET;
  server.sin_port = htons(portserver);
  server.sin_addr.s_addr = INADDR_ANY;
  st = bind(soc,(const struct sockaddr *)&server,sizeof(server));
  if (st!=0) {
     printf("invalid bind; st=%d\n",st);
     exit(-1);
   }
  printf("waiting for a new connection from clients\n");   
  st = listen(soc,5);
  if (st!=0) {
     printf("invalid listen\n");
     return (-1);
   }
  s  = accept(soc,(struct sockaddr *)&client,&lgclient);
  if (s==-1) {
     printf("invalid accept");
     return -1;
   }
  printf("Connexion acceptee; client %s\n",inet_ntoa(client.sin_addr));
  // la connexion est etablie
 
  strcpy(mes,"Welcome on the file Server donner le nom de l'image avec .jpeg\n");
  st = send(s,mes,strlen(mes),0);
  if (st==-1) {
     printf("error occur on sending the welcome message\n");
     return -1;
   }
   do {
      printf("nom de l'image avec .jpeg\n");
      st = recv(s,&mes,sizeof(mes),0);
	if (strcmp(mes,"end")==0)
		{
		st = send(s,mes,strlen(mes),0);
		break;
		}
      if (st > 0) {
        mes[st] = 0;
        printf("le nom de l'image est: %s\n",mes);
        char comd[]="./v4l2grab -o ";
        strcat(comd,mes);
        int status = system(comd);
}
    } while (strcmp("end",mes)!=0);
  close(s);
  close(soc);
}
