#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int parser(char **u,char **d,char *line)
{
    d[0] = NULL;
    *u++ = strtok(line," \t");
    while(*u = strtok(NULL," \t")){
         if(strcmp(*u, "|") == 0)
         {
          *u = NULL;
           while(*d++ = strtok(NULL," \t"))
           {
             /*empty*/
           }
             return 1;
         }
         u++;
    }
    return 1;
}

main(int argc,char **argv)
{
    int p[2];
    char *upstream[20];
    char *downstream[20];
    int status;
    
    parser(upstream,downstream,argv[1]);
    
        if(downstream[0] == NULL) {
            if(fork() == 0) { /* child */ 
              execvp(upstream[0],upstream);
              printf("%s: not found\n",upstream[0]);
              exit(1);
            }else
            {
                /*parent*/
                wait(0);
            }
        }
        else
        {
            /* we have a pipeline */
            pipe(p);
            if(fork() == 0) {
                /* upstream child */
                dup2(p[1],1);
                close(p[0]);
                execvp(upstream[0],upstream);
                printf("%s: upstream not found\n , %s", upstream[0],upstream[1]);
                exit(1);
            }
            if(fork() == 0)
            {
                /* downstream child */
                dup2(p[0],0);
                close(p[1]);
                execvp(downstream[0],downstream);
                printf("%s: downstream not found - %d \n", downstream[0],status);
                exit(1);
           }
           else {
               /* parent */
               close(p[0]);
               close(p[1]);
               
               wait(0);
               wait(0);
           }
        }
    
}
