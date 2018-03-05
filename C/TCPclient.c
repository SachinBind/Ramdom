#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <net/if.h>
#include <unistd.h>
#include <errno.h>

#define PORT 12123

int main(int argc, char *argv[]){
  /********* TCP CLIENT ********/
  
  int clientSocket;
  struct sockaddr_in serverAddress;
  struct hostent *server;
  char buffer[1024];

  // #1, Create a Socket for The Client                                                                    
  clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  if ( clientSocket < 0){
    perror("Could Not Create Socket!");
    exit(EXIT_FAILURE);
  }
  
  // #2, Get the information about the server                                                                
  //server = gethostbyname(""); //IP address of server                                              
  server = gethostbyname( "localhost" ); //Both in the same machine [IP address 127.0.0.1]               
  
  //Error Checking                                                                                     
  if ( server == NULL ){
    printf("\nERROR, no such host...\n");
    exit(EXIT_FAILURE);
  }

  // #3, Stablish Communication with server on the same socket                                          
  bzero( ( char * ) &serverAddress, sizeof( serverAddress ) );
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons( PORT );
  memcpy( &serverAddress.sin_addr, server->h_addr, server->h_length );


  // #4, Connet to the server                                                                      
  if( connect( clientSocket, ( struct sockaddr* )&serverAddress, sizeof( serverAddress) ) < 0 ){
    perror("Error: Could Not Connect To Server!");
    exit( EXIT_FAILURE);
  }

  // USER INPUT                                                                                                           
  printf(" /********* TCP CLIENT ********/\n::");
  bzero( buffer, sizeof( buffer ) );
  gets(buffer);
   
  // #5, Interact     
  write( clientSocket, buffer, strlen(buffer) );
  read( clientSocket, buffer, sizeof( buffer ) );
  printf("Server Said: %s\n", buffer);

  
  return 0;
}
