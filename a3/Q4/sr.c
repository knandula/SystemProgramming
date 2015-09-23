#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#define MAX 80
#define PORT 52288
#define SA struct sockaddr

void func(int sockfd)
{
    char buff[MAX];
    int n,i;
    int sum=0,rev=0;
    
    for(;;)
    {
        bzero(buff,MAX);
        
        read(sockfd,buff,sizeof(buff));
        
        printf("String Received : %s",buff);
        
        for(i=0;i<strlen(buff) - 1;i++)
        {
              sum += (int)buff[i];
        }
        
        bzero(buff,MAX);
        n=0;
        while(sum != 0)
        {
            rev = rev * 10;
            rev = rev + sum%10;
            sum /= 10;
        }
        
        while(rev != 0)
        {
            buff[n++] = '0' + (rev % 10);
            rev /= 10;
        }
        
        printf("Sum Sent : %s\n",buff);
        write(sockfd, buff,sizeof(buff));
        if(strncmp("exit",buff,4)==0)
        {
            printf("Server Exit...\n");
            break;
        }
    }
}
int main()
{
    int sockfd,connfd,len;
    struct sockaddr_in servaddr,cli;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    
    if(sockfd==-1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
        
    bzero(&servaddr,sizeof(servaddr));
    
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(PORT);
    
    if((bind(sockfd,(SA*)&servaddr, sizeof(servaddr)))!=0)
    {
    printf("socket bind failed...\n");
    exit(0);
    }
    else
    printf("Socket successfully binded..\n");
    if((listen(sockfd,5))!=0)
    {
    printf("Listen failed...\n");
    exit(0);
    }
    else
    printf("Server listening..\n");
    
    len=sizeof(cli);
    connfd=accept(sockfd,(SA *)&cli,&len);
    if(connfd<0)
    {
    printf("server acccept failed...\n");
    exit(0);
    }
    else
    printf("server acccept the client...\n");
    func(connfd);
    close(sockfd);
}