#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"headphone-status.h"


void start_checking_headphone_status();


void start_checking_headphone_status()
 {

char *newStatus;

   while(1)  
    {
      system("sleep 1s"); /* check the status every few seconds */
      newStatus=computeStatus(extractRequiredLine()); /*functions from headphone-status.c  file */
       if( (strcmp(newStatus,"OUT"))==0 )
       {
        system("~/Desktop/e4vip/pico2wave.sh \"Please connect the headphone & restart the e4vip \"");	
        system("killall e4vip");  /* kill the process if headphone  is diconnected */
        system("killall sleep");
        
         exit(0); /* if true exit this process as well */

                 }
       else
         {
            continue; /* or else keep checking the status of the headphone */
               }
                       
      }

  }
