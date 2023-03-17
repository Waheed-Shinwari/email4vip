#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

bool isUnseenAvailable(); /* check wheter unseen emails IDs are available */

int SearchMSGid(); /* Extract 1 MSG id from the Unseen MSG ids file */

/* int main(void)
{

int MSGid = SearchMSGid();

printf("MSGid is: %d\n",MSGid);
printf("Unseen Available.?: %d\n",isUnseenAvailable());
   
   } */






int SearchMSGid()
 {
 
 /* Return one ID of the unseen email from the UnseenIDs.txt file */


FILE* file = fopen("UnseenIDs.txt", "r");

char extractedCharacters[16];

fread(extractedCharacters,sizeof(char),15,file);

fclose(file);

static int MSGid;
char *p=extractedCharacters;
  while ( *p )  // While there are more characters to process...
   {     
     if (isdigit(*p))  // Upon finding a digit, ...
          {         
             
             MSGid = atol(p);    // Read a number, OR strtol(p,&p,10)
             //printf("%ld\n", MSGid);        // and print it.
             
            break; //break when we get one digit
           } 
              else 
             {  // Otherwise, move on to the next character.
              p++;
              
              } 
   }

 return MSGid;
  
   }


bool isUnseenAvailable()
 {
    /* returns true if unseen email IDs are available */
    
  FILE* file = fopen("UnseenIDs.txt", "r");

  char extractedCharacters[16];
  bool idFound=0;

  fread(extractedCharacters,sizeof(char),15,file);

  fclose(file);

  static int MSGid;
  char *p=extractedCharacters;
    while ( *p )  // While there are more characters to process...
   {     
     if (isdigit(*p))  // Upon finding a digit, ...
          {         
             
            idFound=1;
             
            break; //break when we get one digit
           } 
              else 
             {  // Otherwise, move on to the next character.
              p++;
              
              } 
   }

   return idFound;

  }





