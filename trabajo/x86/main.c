/* Estos son los ficheros de cabecera usuales */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
 
#define PORT 3550 /* El puerto que será abierto */
#define BACKLOG 1 /* El número de conexiones permitidas */
#define MAXDATASIZE 100 

int main() {
 
   int fd, fd2; /* los ficheros descriptores */
   int numbytes;
   char buf[MAXDATASIZE];
   
   struct sockaddr_in server; /* para la información de la dirección del servidor */
   struct sockaddr_in client; /* para la información de la dirección del cliente */
 
   int sin_size;
 
   printf ("Creacion del socket .... \n");
   /* A continuación la llamada a socket() */
   if ((fd=socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {
      printf("error en socket()\n");
      exit(-1);
   }
 
   server.sin_family = AF_INET;
   server.sin_port = htons(PORT);
   server.sin_addr.s_addr = INADDR_ANY; /* INADDR_ANY coloca nuestra dirección IP automáticamente */
   bzero(&(server.sin_zero),8);         /* escribimos ceros en el reto de la estructura */
   
   printf ("Bind del socket .... \n");
   /* A continuación la llamada a bind() */
   if(bind(fd,(struct sockaddr*)&server, sizeof(struct sockaddr))==-1) {
      printf("error en bind() \n");
      exit(-1);
   }
 
   printf ("Listen del socket .... \n");
   if(listen(fd,BACKLOG) == -1) {  /* llamada a listen() */
      printf("error en listen()\n");
      exit(-1);
   }
 
 //  while(1) {
      printf ("Accept del socket .... \n");
      sin_size=sizeof(struct sockaddr_in);
      
      /* A continuación la llamada a accept() */
      if ((fd2 = accept(fd,(struct sockaddr *)&client, &sin_size))==-1) {
         printf("error en accept()\n");
         exit(-1);
      }
 
      printf("Se obtuvo una conexión desde %s\n",inet_ntoa(client.sin_addr));
      /* que mostrará la IP del cliente */
    
     
      while(1){
      printf ("Enviando datos del servidor ....\n");
      send(fd2,"Conexion exitosa",16,0);
            
      memset (buf,MAXDATASIZE,'\0');
      printf ("Recibiendo datos del cliente ....\n");
      if ((numbytes=recv(fd2,buf,MAXDATASIZE,0)) == -1){
         printf("Error en recv() \n");
         exit(-1);
      }
      if(!strcmp (buf,"END"))break;
      buf[numbytes]=0;
      printf("Mensaje del Cliente: %s\n",buf);
      
      }
 
  // }

   close(fd2); /* cierra fd2 */
   return 0;
}
