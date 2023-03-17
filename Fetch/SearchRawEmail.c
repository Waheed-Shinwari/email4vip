#include<stdio.h>
#include<string.h>
#include<stdbool.h>

bool isEncoded(char *filename);
bool isTextPlain(char *filename);
bool isAudioWav(char *filename);
bool isAudioXWav(char *filename);

bool isAudioMp3(char *filename);
bool isAudioMpeg(char *filename);

bool isMultipartMixed(char *filename);
bool isMultipartAlternative(char *filename);

char *getSubject( char *filename );
char *getFrom( char *filename );


/*
 int main(void)
{

 printf("Yes or No: %d\n",isEncoded("fetchedEmailRaw.txt"));
 printf("is Text Plain.?: %d\n",isTextPlain("fetchedEmailRaw.txt"));
 printf("is audio/wav.?: %d\n",isAudioWav("fetchedEmailRaw.txt"));
 printf("is audio/mp3.?: %d\n",isAudioMp3("fetchedEmailRaw.txt"));
 printf("is audio/mpeg.?: %d\n",isAudioMpeg("fetchedEmailRaw.txt") );

 printf("Subject: %s\n",getSubject("fetchedEmailRaw.txt"));
 printf("Multipart/Mixed.?: %d\nMultipart/Alternative?: %d\n",isMultipartMixed("fetchedEmailRaw.txt"),isMultipartAlternative("fetchedEmailRaw.txt") );
  
   } */


bool isEncoded(char *filename)
 {
     /* Check the file if it contains base64 encoded text or not */

  FILE *fp;

  fp = fopen(filename,"r");

  char line[512];
  bool found=0; /* Initially 0, Change to 1 only if "base64" is found */

  while ( fgets(line, 512, fp) !=NULL )
       {
        
       if( strstr(line,"Content-Transfer-Encoding: base64") )
         {
          //printf("Found line: %s\n",line);   
          found=1; /* Change to 1 only if "base64" is found */
          }
        else
          {
           //printf("Not found\n");
          
          
           }
       }
   fclose(fp); /* close the file pointer */

 return found; /* return yes or no i.e 1 or 0 */
  }


bool isTextPlain(char *filename)
 {
     /* Check the file if it contains "Content-Type: text/plain" text or not */

  FILE *fp;

  fp = fopen(filename,"r");

  char line[512];
  bool found=0; /* Initially 0, Change to 1 only if "text/plain" is found */

  while ( fgets(line, 512, fp) !=NULL )
       {
        
       if( strstr(line,"Content-Type: text/plain") )
         {
          //printf("Found line: %s\n",line);   
          found=1; /* Change to 1 only if "text/plain" is found */
          }
        else
          {
           //printf("Not found\n");
          
          
           }
       }
   fclose(fp); /* close the file pointer */

 return found; /* return yes or no i.e 1 or 0 */
  }

bool isAudioWav(char *filename)
 {
     /* Check the file if it contains "Content-Type: audio/wav" text or not */

  FILE *fp;

  fp = fopen(filename,"r");

  char line[512];
  bool found=0; /* Initially 0, Change to 1 only if "audio/wav" is found */

  while ( fgets(line, 512, fp) !=NULL )
       {
        
       if( strstr(line,"Content-Type: audio/wav") )
         {
          //printf("Found line: %s\n",line);   
          found=1; /* Change to 1 only if "Content-Type: audio/wav" is found */
          }
        else
          {
           //printf("Not found\n");
          
          
           }
       }
   fclose(fp); /* close the file pointer */

 return found; /* return yes or no i.e 1 or 0 */
  }


bool isAudioXWav(char *filename)
 {
     /* Check the file if it contains "Content-Type: audio/x-wav" text or not */

  FILE *fp;

  fp = fopen(filename,"r");

  char line[512];
  bool found=0; /* Initially 0, Change to 1 only if "audio/x-wav" is found */

  while ( fgets(line, 512, fp) !=NULL )
       {
        
       if( strstr(line,"Content-Type: audio/x-wav") )
         {
          //printf("Found line: %s\n",line);   
          found=1; /* Change to 1 only if "Content-Type: audio/x-wav" is found */
          }
        else
          {
           //printf("Not found\n");
          
          
           }
       }
   fclose(fp); /* close the file pointer */

 return found; /* return yes or no i.e 1 or 0 */
  }







bool isAudioMp3(char *filename)
 {
     /* Check the file if it contains "Content-Type: audio/mp3" text or not */

  FILE *fp;

  fp = fopen(filename,"r");

  char line[512];
  bool found=0; /* Initially 0, Change to 1 only if "audio/mp3" is found */

  while ( fgets(line, 512, fp) !=NULL )
       {
        
       if( strstr(line,"Content-Type: audio/mp3") )
         {
          //printf("Found line: %s\n",line);   
          found=1; /* Change to 1 only if "Content-Type: audio/mp3" is found */
          }
        else
          {
           //printf("Not found\n");
          
          
           }
       }
   fclose(fp); /* close the file pointer */

 return found; /* return yes or no i.e 1 or 0 */

  }



bool isAudioMpeg(char *filename)
 {
     /* Check the file if it contains "Content-Type: audio/mpeg" text or not */

  FILE *fp;

  fp = fopen(filename,"r");

  char line[512];
  bool found=0; /* Initially 0, Change to 1 only if "audio/mpeg" is found */

  while ( fgets(line, 512, fp) !=NULL )
       {
        
       if( strstr(line,"Content-Type: audio/mpeg") )
         {
          //printf("Found line: %s\n",line);   
          found=1; /* Change to 1 only if "Content-Type: audio/mpeg" is found */
          }
        else
          {
           //printf("Not found\n");
          
          
           }
       }
   fclose(fp); /* close the file pointer */

 return found; /* return yes or no i.e 1 or 0 */

  }



bool isMultipartMixed(char *filename)
 {
     /* multipart/mixed type of emails have text and attachments, while multipart/alternative have text/html and text/plain type of contents */

     /* Check the file if it contains "Content-Type: multipart/mixed" text or not */

  FILE *fp;

  fp = fopen(filename,"r");

  char line[512];
  bool found=0; /* Initially 0, Change to 1 only if "multipart/mixed" is found */

  while ( fgets(line, 512, fp) !=NULL )
       {
        
       if( strstr(line,"Content-Type: multipart/mixed") )
         {
          //printf("Found line: %s\n",line);   
          found=1; /* Change to 1 only if "Content-Type: multipart/mixed" is found */
          }
        else
          {
           //printf("Not found\n");
          
          
           }
       }
   fclose(fp); /* close the file pointer */

 return found; /* return yes or no i.e 1 or 0 */

  }


bool isMultipartAlternative(char *filename)
 {
     /* multipart/alternative is for sending text/html and text/plain versions of a message, and multipart/mixed is for adding attachments. */

     /* Check the file if it contains "Content-Type: multipart/alternative" text or not */

  FILE *fp;

  fp = fopen(filename,"r");

  char line[512];
  bool found=0; /* Initially 0, Change to 1 only if "multipart/alternative" is found */

  while ( fgets(line, 512, fp) !=NULL )
       {
        
       if( strstr(line,"Content-Type: multipart/alternative") )
         {
          //printf("Found line: %s\n",line);   
          found=1; /* Change to 1 only if "Content-Type: multipart/alternative" is found */
          }
        else
          {
           //printf("Not found\n");
          
          
           }
       }
   fclose(fp); /* close the file pointer */

 return found; /* return yes or no i.e 1 or 0 */
 
 }









char *getSubject( char *filename )
 {
        /* extract Subject from the "fetchedEmailRaw.txt" or fetchedHeaders.txt file */

   FILE *file = fopen(filename, "r");
   int RequiredLineNumber = 1; /* The line where the "Subject:" Header field is located */
   static char extractedLine[100];  
   
  while ( fgets(extractedLine, 100, file) !=NULL )
        {
         extractedLine[strlen(extractedLine)-1]='\0'; /* remove the trailing new line char */
         if( strstr(extractedLine,"Subject:") )
           {
            
            break; /* break the loop if key word is found in this line */
            
            }
          else
            {
              RequiredLineNumber++; /* else increment to the next line for searching */
             
          
          
             }
         }



    fclose(file);


 return (extractedLine+8); /* Return string that follows the "Subject:" */


  }

char *getFrom( char *filename )
 {
         /* extract "FROM" from the "fetchedEmailRaw.txt"  or fetchedHeaders.txt file */
   FILE *file = fopen(filename, "r");
   int RequiredLineNumber = 0; /* The line where "From Header Field" is located */
   static char extractedLine[100];  

  while ( fgets(extractedLine, 100, file) !=NULL )
        {
         extractedLine[strlen(extractedLine)-1]='\0'; /* remove the trailing new line char */
         if( strstr(extractedLine,"From:") )
           {
              
            break; /* break the loop if key word is found in this line */
            
            }
          else
            {
              RequiredLineNumber++; /* else increment to the next line for searching */
            
          
             }
         }

    fclose(file);


 return (extractedLine+5); /* Return string that follows the string "From:" */


  }



