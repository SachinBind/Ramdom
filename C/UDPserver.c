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
 /********* UDP Server ************/
  
  int serverSocket;
  int bytes_read;
  char buffer[1024];
  socklen_t addr_len;
  struct sockaddr_in server_addr , client_addr;
  
  addr_len = sizeof( struct sockaddr );
  
  // #1, Get a Socket For The Server 
  if( ( serverSocket = socket( AF_INET, SOCK_DGRAM, 0 ) ) == -1 ) {
    perror( "Error Creating Socket" );
    exit(1);
  }

  // #2, Tell The Kernel Who We are
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons( PORT );
  server_addr.sin_addr.s_addr = INADDR_ANY;
  bzero( &( server_addr.sin_zero ), 8 );

  // #3, Bind To The Socket. aka Lets Become A Server
  if( bind( serverSocket, ( struct sockaddr * )&server_addr, sizeof( struct sockaddr ) ) == -1 ){
    perror("Error Binding To The Socket");
    exit(1);
  }

  // #4, Interact
  printf(" /********* UDP Server ************/\n");
  bytes_read = recvfrom(serverSocket,buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &addr_len);
  buffer[bytes_read] = 0;
  printf("\n(%s , %d) said : %s\n",inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);
  sendto(serverSocket, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, sizeof(struct sockaddr));
  
  
  return 0;
}
