#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



int main()
{
  int sockint, s, namelen, client_address_size;
  struct sockaddr_in client, server;
  char buf[150];
  int sum=0,i=0;
 
  s = socket(AF_INET, SOCK_DGRAM, 0);
  
    if( s == -1 )
     {
         printf("Failed to create socket");
         return -1;
     }
    else
     {
     printf("Socket Initialized.\n");
     }
 
    server.sin_family = AF_INET;
    server.sin_port = 0; /* use first available port number */
    server.sin_addr.s_addr = INADDR_ANY;

    if(bind(s, &server, sizeof(server)) < 0) {
    printf("Error binding server.\n");
    exit(3);
    }

    namelen = sizeof(server);
    if(getsockname( s, (struct sockaddr *) &server, &namelen) < 0 )
    {
    perror("getsockname()\n");
    return -1;
    }
    printf("listening on port %d .. \n",ntohs(server.sin_port));
    while(1)  
    {
    client_address_size = sizeof( client );
    if(recvfrom(s,buf,sizeof(buf), 0, (struct sockaddr *) &client, &client_address_size) >= 0 )
    {
        printf("String received : %s\n",buf);
    }
    }
    
    return 0;
}