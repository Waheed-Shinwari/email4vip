#include<stdio.h>
#include<stdlib.h>
#include <pwd.h>



int main(void)
 {

  char *homedir = getenv("HOME"); /* get user home directory */

 system("sudo apt-get install xbindkeys");
 
 char filename[50];
 sprintf(filename,"%s/.xbindkeysrc",homedir);

 FILE *fp=fopen(filename,"w");
 
 char query[150]="\"~/Desktop/e4vip/run-e4vip.sh\"\n  control+e\n";

  //printf("%s",query);
 fputs(query,fp);
 
 fclose(fp);
 
 system("xbindkeys");

 }

