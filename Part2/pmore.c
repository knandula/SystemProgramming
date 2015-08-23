
/* implemenation of OS assignment part 3 , using Split + Tac */

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <termios.h>

#define MAX_LINE_SIZE 4096

int getch(void);   // wait for next keystroke (no echo)
int getchp(void);  // check for pending keystrokes (no echo)
/* reads from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

/* reads from keypress, echoes */
int getche(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
int main (int argc, char **argv)
{
int i,n,j,p=0;
int nlines=0;
int linecounter=1;
FILE *ptr_readfile;
FILE *ptr_writefile;
struct dirent **namelist;
char inputfilename[500];
char line[MAX_LINE_SIZE];
int counter =0 ;


int slines = 0;

nlines = atoi(argv[1]);
slines = nlines;

ptr_readfile = fopen(argv[2],"r");
if (!ptr_readfile)
{
    printf("unable to read file");
    return 1;
}

while (fgets(line, sizeof line, ptr_readfile)!=NULL) {
    if (linecounter == nlines) {
       int key;
       key = getch();
       if(key == 10){
          linecounter = 0 ;
          nlines = 1;
       }else if(key == 32)
       {
          linecounter = 0;
          nlines = slines;
       }else if(key == 113) return 0;
    }

    printf("%s",line);
    linecounter++;
    counter++;

}
	fclose(ptr_readfile);

return 0;
}

