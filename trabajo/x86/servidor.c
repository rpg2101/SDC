#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#define BUFFSIZE 5
#define IP "192.168.1.1"
#define IPBC "192.168.1.200"

#define PORT     1050
#define PORTDATA 1051


int main(void){

  int socket_fd    = socket(AF_INET, SOCK_DGRAM, 0);
  int socket_datos = socket(AF_INET, SOCK_DGRAM, 0);
  
  char buffer[BUFFSIZE] = "";
  int i  , registrado;
  i = 0;
  registrado = 0;

  struct sockaddr_in src_addr;
  struct sockaddr_in dest_addr;
  socklen_t len = sizeof dest_addr;
  
  src_addr.sin_family = AF_INET;
  src_addr.sin_port = htons(PORT);
  src_addr.sin_addr.s_addr = inet_addr(IP);

  dest_addr.sin_family = AF_INET;
  dest_addr.sin_port = htons(PORT);
  dest_addr.sin_addr.s_addr = inet_addr(IPBC);

  struct sockaddr_in src_addr_datos;
  struct sockaddr_in dest_addr_datos;
  socklen_t len_datos = sizeof dest_addr_datos;
  src_addr_datos.sin_family = AF_INET;
  src_addr_datos.sin_port = htons(PORTDATA);
  src_addr_datos.sin_addr.s_addr = inet_addr(IP);


  if(socket_fd==-1)
    perror("socket");
  if(bind(socket_fd, (struct sockaddr*)&src_addr, sizeof(src_addr))==-1)
    perror("bind");

  while(1) {

  printf ("enviando beacon ...\n");
  if (!registrado) {
    if(sendto(socket_fd, "BEACON", sizeof("BEACON"), 0,(struct sockaddr*)&dest_addr, sizeof(dest_addr))==-1) perror("sendto");
  }

  
 }

  if(recvfrom(socket_fd, buffer, 2, 0, (struct sockaddr*)&dest_addr, &len) == -1)
    perror("recvfrom");
  
  if (!strcmp(buffer,"HELLO")){
	 if(sendto(socket_fd, "ACK", sizeof("ACK"), 0,(struct sockaddr*)&dest_addr, sizeof(dest_addr))==-1) perror("sendto");
	 registrado = 1;   
	 dest_addr_datos = dest_addr;
         src_addr_datos.sin_port = htons(PORTDATA);
         
  }	

  if(socket_datos==-1)
  perror("socketdatos");
  if(bind(socket_datos, (struct sockaddr*)&src_addr_datos, sizeof(src_addr_datos))==-1)
    perror("bind");

  printf ("solicitando datos ... \n");
  if(sendto(socket_datos, buffer, 2, 0,(struct sockaddr*)&dest_addr_datos, sizeof(dest_addr_datos))==-1)
    perror("sendto");
  if(recvfrom(socket_datos, buffer, 2, 0, (struct sockaddr*)&dest_addr_datos, &len_datos) == -1)
    perror("recvfrom");

   printf ("datos recibidos ... ");
   printf ("%s",buffer);
   printf ("\n");

//  }
  if(close(socket_fd)==-1)
    perror("close");
  
  return 0;
}
