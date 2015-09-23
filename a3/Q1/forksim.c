#include  <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int  main(void)
{
    int sum=0;
    int i=0;
    int j=0;
    int col,row;
    scanf("%d",&row);
    scanf("%d",&col);
    int arr[row][col];
    
    
    for(i=0;i<row;i++)    
      for(j=0;j<col;j++)
        scanf("%d",&arr[i][j]);
    
   
   for ( i=0;i<row;i++)
    {
        pid_t pid = fork();
        pid_t cpid = getpid();
        pid_t ppid = getppid();
  
        for (j=0;j<col;j++)
            sum += arr[i][j];
            
        if(pid == 0)
        {
        printf("Child pid : %d, Sum of row : %d is : %d\n",getpid(),i,sum);
        exit(0);
        }
       sum=0;
       
        
    }
}

