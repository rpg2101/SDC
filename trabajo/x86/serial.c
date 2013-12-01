#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */


void recibir(char* buffer, int fd ){
  while (strcmp(buffer,"\nTKN")){
  	memset (buffer, '\0' , sizeof(buffer));
	int n = read(fd, buffer, sizeof(buffer));
  	if (n < 0) fputs("read failed!\n", stderr);
  	if ( n>0 ) printf("%s",buffer);
  }
}

void main(int argc, char *argv[]) {
  int fd; /* File descriptor for the port */


  fd = open(argv[1], O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1) {
    perror("open_port: Unable to open device - ");
  }
  else
    fcntl(fd, F_SETFL, 0);
 

  char in[4];
  char buffer[32];
  int n;
  while(1){
//  	recibir (buffer , fd);  
  	
        memset (in, '\0' , 4);
        strcpy(in ,"1111");
	n = write(fd, in, sizeof(in));
	
//if (!strcmp (in,"1")) n = write(fd, "OPC1", 4);
//	else if (!strcmp (in,"2")) n = write(fd, "OPC2", 4);
//  	else if (!strcmp (in,"3")) n = write(fd, "OPC3", 4);
//  	else if (!strcmp (in,"4")) n = write(fd, "OPC4", 4);
  	 
  	if (n < 0) fputs("write() failed!\n", stderr);
	
	memset (buffer, '\0' ,32);
	n = read(fd, buffer, sizeof(buffer));
  	if (n < 0) fputs("read failed!\n", stderr);
	printf("%s",buffer);	
  }
  
}

   

