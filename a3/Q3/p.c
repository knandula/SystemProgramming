//producer 

#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#define memsize 500

int main(int argc,char **argv)
{
    int startno,length;
    int shmid;
    key_t key;
    int *shm,*s;
    int n, first = 0, second = 1, next, c;
    
    int i;
    startno =atoi(argv[1]);
    length = atoi(argv[2]);
    first = startno;
    key=5556;
    
    if((shmid = shmget(key,memsize,IPC_CREAT | 0666)) < 0)
    {
     perror("shmget");
        return -1;
    }
    
    if((shm = shmat(shmid,NULL,0)) == (int *)-1)
    {
     perror("shmat");
        return -1;
    }
    
   s=shm;
   
   for ( c = startno ; c < length ; c++ )
   {
      if ( c <= 1 )
         next = c;
      else
      {
         next = first + second;
         first = second;
         second = next;
      }
      *s++ = next;
   }
    
    while(*shm != '*')
       sleep(1);
       
     return 0;
}
