#include "funsock.h"
#include <unistd.h>
#include <stdio.h>
//#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


//----------------------------Crear socket----------------------------------------
int conectar(char* direccion,int puerto){
    int fd;
    struct hostent *he;
    struct sockaddr_in server;

    if ((he=gethostbyname(direccion))==NULL){
       /* llamada a gethostbyname() */
       printf("gethostbyname() error\n");
       return -1;
    }

    printf ("Creando socket ....\n");
    if ((fd=socket(AF_INET, SOCK_STREAM, 0))==-1){
       /* llamada a socket() */
       printf("socket() error\n");
       return -1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(puerto);
    /* htons() es necesaria nuevamente ;-o */
    server.sin_addr = *((struct in_addr *)he->h_addr);
    /*he->h_addr pasa la información de ``*he'' a "h_addr" */
    bzero(&(server.sin_zero),8);

    printf ("Conectando al servidor ....\n");
    if(connect(fd, (struct sockaddr *)&server,
       sizeof(struct sockaddr))==-1){
       /* llamada a connect() */
       printf("connect() error\n");
       return -1;
    }

    return fd;

}

void recibir (int fd, char* c){
    int numbytes;
    char buf[MAXDATASIZE];

    printf ("Recibiendo datos del servidor ....\n");
    if ((numbytes=recv(fd,buf,MAXDATASIZE,0)) == -1){
       /* llamada a recv() */
       printf("Error en recv() \n");
       //exit(-1);
    }
    buf[numbytes]='\0';
    printf("Mensaje del Servidor: %s--\n",buf);
    strncpy (c, buf, MAXDATASIZE);
}

void enviar (int fd,char* d){
    printf ("Enviado datos del servidor ....\n");
    send(fd,d,strlen(d),0);
}


void cerrar(int fd){
    close(fd);   /* cerramos fd =) */
}
