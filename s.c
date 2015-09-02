#define _GNU_SOURCE
#include<sys/stat.h>
#include<fcntl.h>
#include<dirent.h>
#include<unistd.h>
#include<stdio.h>
#include<time.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

int mySort(const struct dirent **e1,const struct dirent **e2);
int (*fnPtr)(const struct dirent **e1,const struct dirent **e2);
int file_select(const struct dirent *entry);
int (*fnP)(const struct dirent *entry);

int mySort(const struct dirent **e1,const struct dirent **e2)
{
   const char *a = (*e1)->d_name;
   const char *b = (*e2)->d_name;
   return strcmp(a,b);
}

int file_select(const struct dirent *entry)
{
     if(strcmp(entry->d_name,"..") !=0 && strcmp(entry->d_name,".") !=0 && entry->d_type != DT_DIR)
        return -1;
return 0;
}



int main(int argc, char *argv[])
{
    int lflag=0;
    int aflag=0;
    int tflag=0;
    int iflag=0;
    int Sflag=0;
    int Rflag=0;
    int nflag=0;
    int opt;
    int index;
    DIR *p;
    struct dirent **namelist;
    opterr=0;

    while((opt=getopt(argc,argv,"latiSR")) != -1)
     switch(opt)
      {
          case 'l':
             lflag=1;
             break;
          case 'a':
             aflag=1;
             break;
          case 't':
             tflag=1;
             break;
          case 'S':
             Sflag=1;
             break;
          case 'R':
             Rflag=1;
             break;
          case '?':
               fprintf(stderr,"ls: invalid option -- '%c'\n",optopt);
             break;
          default:
              nflag=1;
              fprintf(stderr,"No Options");
            abort ();
      }

 if(lflag == 0 && aflag == 0 && tflag == 0 && Sflag == 0 && Rflag == 0) // ls without any flag, default ls in current directory
 {
   int n;
   int i=0;
   n = scandir(".",&namelist,file_select,alphasort);
   if(n<0)
     return -1;
    else {
        while(i<n){
         if(namelist[i]->d_type == DT_DIR)
           printf("%s%s\n",KBLU,namelist[i]->d_name);
           else
            printf("%s%s\n",KWHT,namelist[i]->d_name);

         free(namelist[i]);
         i++;
        }
        free(namelist);


    }
 }
return 0;
}


