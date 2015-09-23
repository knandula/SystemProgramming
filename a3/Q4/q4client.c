#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

main( argc, argv)
int argc;
char **argv;
{
	int s,server_address_size;
	unsigned short port;
	struct sockaddr_in server;
	char buf[150];
	port = htons(atoi( argv[2] ));
	s = socket(AF_INET, SOCK_DGRAM, 0);

	server.sin_family = AF_INET;
	server.sin_port = port;
	server.sin_addr.s_addr = inet_addr(argv[1]);
    
    while(1)
    {
        printf("Type string to send :");
        scanf("%s",buf);
        sendto(s,buf,(strlen(buf)+1),0,&server,sizeof(server));
  
    
        
        //if(strcmp(buf,"quit") != 0)
        // {
           //  close(s);
           //  printf("Socket closed.\n");
        // }
    }
    
}