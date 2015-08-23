/* implemenation of OS assignment part 3 , using Split + Tac */

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>


#define MAX_LINE_SIZE 4096

int EndsWith(const char *str, const char *suffix)
{
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

FILE *openforwrite(int filecounter,char *output,char *filename) {
	char fileoutputname[500];
	sprintf(fileoutputname, "%s_%s_%d",output,filename,filecounter);
	return fopen(fileoutputname, "w");
}




int filter(const struct dirent *dir)
{
const char *s = dir->d_name;
if((strcmp(s, ".") == 0) || (strcmp(s, "..") == 0))
 return 0;
else
 return 1;
}

struct stat st = {0};

int main (int argc, char **argv)
{

//Create the destination directory structure if not exists

//Loop through files in the source path

   //Get the current file[0]
   // Read through the files based on the number of lines
   // store each lines into an array
   // write to the new files in reveroder by looping the array
  //Move on to create a new parts, GOTO

int i,n,j,p=0;
int nlines=0;
FILE *ptr_readfile;
FILE *ptr_writefile;
struct dirent **namelist;
char inputfilename[500];

if (argc < 4)
{
 printf ("usage: SplitTac needs three arguments..\n ");
 return -1;
}

//Get the source dir path
nlines = atoi(argv[3]);

if(!EndsWith(argv[2], "/"))
{
argv[2] = strcat(argv[2],"//");
}

if (stat(argv[2], &st) == -1) {
    mkdir(argv[2], 0700);
}

nlines++;
char buf[nlines][MAX_LINE_SIZE];

n = scandir(argv[1], &namelist, filter, alphasort);
if (n < 0)
perror("scandir");
else {
for (i = 0; i < n; i++) {
	char line [128]; /* or some other suitable maximum line size */
	int filecounter=1, linecounter=1;
	sprintf(inputfilename, "%s//%s",argv[1],namelist[i]->d_name);
	ptr_readfile = fopen(inputfilename,"r");

	if (!ptr_readfile)
		{
		printf("unable to read file");
		return 1;
		}

	ptr_writefile = openforwrite(filecounter,argv[2],namelist[i]->d_name);

	while (fgets(line, sizeof line, ptr_readfile)!=NULL) {

		if (linecounter == nlines) {
			for(j=nlines - 1;j>=0;--j)
			{
			  fprintf(ptr_writefile,"%s", buf[j]);
			  strcpy(buf[j],"");
            }
			p=0;
			fclose(ptr_writefile);
			linecounter = 1;
			filecounter++;
			ptr_writefile = openforwrite(filecounter,argv[2],namelist[i]->d_name);
			if (!ptr_writefile)
			return 1;

		}
		strcpy(buf[p], line);
		p++;
		linecounter++;
	}


	for(j=nlines - 1;j>=0;--j)
	  {
           fprintf(ptr_writefile,"%s", buf[j]);

       }

    fclose(ptr_writefile);
	fclose(ptr_readfile);
        printf("%s\n", namelist[i]->d_name);
    free(namelist[i]);
    }
}

free(namelist);

return 0;
}


