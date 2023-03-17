#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void record_voicmail();




void record_voicmail()
 {

     char confirm='n';

     while(confirm !='y' && confirm !='Y')
      {  
     system("~/Desktop/e4vip/pico2wave.sh \"Maximum limit is one minute, Press Control C to stop\"");
     system("arecord -d 60 voicemail.wav");
     system("~/Desktop/e4vip/pico2wave.sh \"Your recorded message is\"");
     system("aplay ./voicemail.wav");  
     
  system("~/Desktop/e4vip/pico2wave.sh \"Enter Y to confirm or Enter any other key to re record your message\"");
     scanf(" %c", &confirm);   
    
      }

            
 
 }



