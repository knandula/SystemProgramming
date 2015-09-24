#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *cmd1[] = { "ls","-l -s",0};
char *cmd2[] = { "wc","-l -s",0};

void lhs(int pfd[]);
void rhs(int pfd[]);

int main(int argc, char **argv)
{
    const char s[2] = "|";
	int pid, status;
	int fd[2];
	int i=0,j,k;
    char v;
    char *lcmd;
    char *rcmd;
    
    
    lcmd = strtok(argv[1], s); 
    rcmd = strtok(NULL, s); 
    
   
   
   printf ("%s\t",lcmd);
   printf ("%s\t",rcmd); 


   cmd1[0] = lcmd;
   cmd2[0] = rcmd;
  
	
	
	pipe(fd);
	lhs(fd); // command 1
	rhs(fd); // command 2
	close(fd[0]); close(fd[1]);
	exit(0);
}


void lhs(int pfd[])	
{
	int pid;
	switch (pid = fork()) {
	case 0: 
		dup2(pfd[1], 1);
		close(pfd[0]);
		execvp(cmd1[0], cmd1);
		perror(cmd1[0]);
	default: 
		break;
	case -1:
		perror("fork");
		exit(1);
	}
}

void rhs(int pfd[])	
{
	int pid;
	switch (pid = fork()) {
	case 0: 
		dup2(pfd[0],0);
		close(pfd[1]);
		execvp(cmd2[0],cmd2);
		perror(cmd2[0]);
	default:
		break;

	case -1:
		perror("fork");
		exit(1);
	}
}
