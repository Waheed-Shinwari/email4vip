#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Send/headphone-status.h"
#include<stdbool.h>

void send_voicemail();
void send_doc();
void send123();
void fetch();

int main(void)
{
 

            //char *email=getEmailID();
           // char *pass=getPassword();
            //record_voicmail();
            //char *To="example@gmail.com";
            //char *subject="e4vip test";
            //sendEmail(email,pass,To,subject);
            //printf("Email sent \n");
            //system("killall ./e4vip");

 
   char input;
while(input != 's' && input != 'S' && input != 'f' &&  input != 'F')
   {
      
      system("~/Desktop/e4vip/pico2wave.sh \"To Send an Email enter S, or F to fetch an email\"");
      scanf(" %1c*[^\n",&input);    
      
        } 

	switch(input)
      {
        case 'S':
            send123();
        break;
	case 's':
            send123();
        break;
        
        case 'F':
            fetch();
        break;
        case 'f':
            fetch();
        break;
        default:
            system("~/Desktop/e4vip/pico2wave.sh \"Unkown Choice, system exiting now\"");
            exit(0);
       
         }
 
  

   } 


void send123()
 {
     char choice;
     
     while(choice != 'D' && choice != 'd' && choice != 'V' && choice != 'v' )
         {
               
          system("~/Desktop/e4vip/pico2wave.sh \"To send a word processing document enter D, or V to send a voice mail\"");
                
        scanf("%1c*[^\n]",&choice); //read only one character and ignore the rest of them

 
            }


             switch(choice)
               {
                case 'D':
                 send_doc();
                 break;
                 
               case 'd':
                send_doc();
                break;

               case 'V':
               send_voicemail();
               break;
         
               case 'v':
               send_voicemail();
               break;
               
               default:
                system("~/Desktop/e4vip/pico2wave.sh \"Unkown Choice, system exiting now\"");
                exit(0);
                }



       }






void send_voicemail()
 {
     pid_t child;
     if( (child=fork()) ) 
       { 
            bool isAuthentic=0;
            char *email;
            char *pass;
           while( isAuthentic != 1 )
            {
                 email=getEmailID();
                 pass=getPassword();
            
            if(isAuthentic_SMTP(email,pass) ) /* Check pass and email matches */
              {
                  isAuthentic=1;
               }
             else
               {
                  isAuthentic=0;
                }
              
              }
           
            record_voicmail();
            char *To=getReciever();
            char *subject=inputSubject();
            sendEmail(email,pass,To,subject);

            char query[50];
            sprintf(query,"~/Desktop/e4vip/pico2wave.sh \"Your email is successfully sent to %s Now exiting\"",To);
            system(query);
           
            //printf("child id=%d\n",child);
            system("killall e4vip");
            exit(0); 



             
            
             }
     else {
           
            //child process 

              start_checking_headphone_status();
         
             exit(0);


             }

 
    } 





void send_doc()
 {
     pid_t child;
     if( (child=fork()) ) 
       { 
            bool isAuthentic=0;
            char *email;
            char *pass;
           while( isAuthentic != 1 )
            {
                 email=getEmailID();
                 pass=getPassword();
            
            if(isAuthentic_SMTP(email,pass) ) /* Check pass and email matches */
              {
                  isAuthentic=1;
               }
             else
               {
                  isAuthentic=0;
                }
              
              }
             

            char *To=getReciever();
            char *subject=inputSubject();
            sendDocEmail( email, pass, To, subject );

            char query[50];
            sprintf(query,"~/Desktop/e4vip/pico2wave.sh \"Your email is successfully sent to %s Now exiting\"",To);
            system(query);
           
            //printf("child id=%d\n",child);
            system("killall e4vip");
            exit(0); 



             
            
             }
     else {
           
            //child process 

              start_checking_headphone_status();
         
             exit(0);


             }


 
    } 





void fetch()
 {

     pid_t child;
     if( (child=fork()) ) 
       { 
             
  
            bool isAuthentic=0;
            char *email;
            char *pass;
           while( isAuthentic != 1 )
            {
                 email=getEmailID();
                 pass=getPassword();
            
            if(isAuthentic_IMAP(email,pass) ) /* Check pass and email matches */
              {
                  isAuthentic=1;
               }
             else
               {
                  isAuthentic=0;
                }
              
              }


            fetchEmail(email,pass);

            system("~/Desktop/e4vip/pico2wave.sh \"To check again please start back Now exiting\"");
           
            //printf("child id=%d\n",child);
            system("killall e4vip");
            exit(0); 



             
            
             }
     else {
           
            //child process 

              start_checking_headphone_status();
         
             exit(0);


             }




       }


