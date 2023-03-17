
                                           
        /* This file define functions to get user credentials */



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

char *getEmailID();
char *getPassword();
char *getReciever();
char *inputSubject();

/*  int main()
{
   
   char *email=getEmailID();
   //char *pass=getPassword();
  //char *subject=getSubject();
   
   //printf("Password:%s\n",pass); 
  //printf("Subject:%s\n",subject);
  printf("Email:%s\n",email);

} */



char *getEmailID()
  {

        static char email[100];
        char reply[150];
        char confirm='n'; /* Default No */

        bool isValid=0; /* To make sure email addr is in a valid format */        
       
         while(confirm != 'y' && confirm != 'Y' || isValid !=1 ) 
          {        
        system("~/Desktop/e4vip/pico2wave.sh \"Please Enter Your Email ID And Press Enter Button\"");
       system("stty -echo");  /* echo on*/
         scanf("%s",email);
        //fgets(email,100,stdin);
       system("stty echo");  /* echo off */

        sprintf(reply,"~/Desktop/e4vip/pico2wave.sh \"Your Email ID is %s Press Y to confirm or Any Key to Re-Enter your Email id\"",email);
        system(reply);
        
        scanf(" %c", &confirm); /* The %c specifier doesn't skip blanks,tabs etc so an extra space/blank is added */
                       
             
        if(isEmail(email) )
           {
            isValid=1;
           }
         else
          {
            isValid=0;
          }
     
    
         }
             

         return email; /* return the email id */
                   
       }


char *getPassword()
   {
        static char password[100];
        char reply[150];
        char confirm='n'; /* Default No */
        
        while(confirm != 'y' && confirm != 'Y') 
         {        
        system("~/Desktop/e4vip/pico2wave.sh \"Please Enter Your Password And Press Enter Button\"");
        
        system("stty -echo");
        scanf("%s",password);
        system("stty echo");

        sprintf(reply,"~/Desktop/e4vip/pico2wave.sh \"Your Password is %s Press Y to confirm or Any Key to Re-Enter your Password\"",password);
        system(reply);
        
        scanf(" %c", &confirm); /* The %c specifier doesn't skip blanks,tabs etc so an extra space/blank is added */
                       
                     }
        
         return password; /* return the password */
                   
                         
           }


char *getReciever()
  {

        static char RecieverEmail[100];
        char reply[150];
        char confirm='n'; /* Default No */
        
        while(confirm != 'y' && confirm != 'Y') 
         {        
        system("~/Desktop/e4vip/pico2wave.sh \"Please Enter Recipient Email ID And Press Enter Button\"");
        system("stty -echo");
        scanf("%s",RecieverEmail);
        system("stty echo");
 
        sprintf(reply,"~/Desktop/e4vip/pico2wave.sh \"Your Recipient is %s Press Y to confirm or Any Key to Re-Enter Recipient\"",RecieverEmail);
        system(reply);
        
        scanf(" %c", &confirm); /* The %c specifier doesn't skip blanks,tabs etc so an extra space/blank is added */
                       
                     }
  

         return RecieverEmail; /* return the email id */
                   
       }


char *inputSubject()
  {
    
        static char EmailSubject[120];
        char reply[150];
        char confirm='n'; /* Default No */
        
        while(confirm != 'y' && confirm != 'Y') 
         {        
        system("~/Desktop/e4vip/pico2wave.sh \"Please Enter Email Subject And Press Enter Button\"");
  
        system("stty -echo");
        scanf(" %[^\n]",EmailSubject); /* Read untill new line */
        system("stty echo");

        sprintf(reply,"~/Desktop/e4vip/pico2wave.sh \"The Subject is %s Press Y to confirm or Any Key to Re-Enter Email Subject\"",EmailSubject);
        system(reply);
        
        scanf(" %c", &confirm); /* The %c specifier doesn't skip blanks,tabs etc so an extra space/blank is added */
                       
                     }
  

         return EmailSubject; /* return the email id */


 }
