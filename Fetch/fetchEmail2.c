#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<regex.h>
#include <curl/curl.h>
#include<stdbool.h>

void SearchUnseen( CURL *curl, CURLcode res );
void FetchUnseenRaw( CURL *curl, CURLcode res, int msgID ); /* Fetch 1 unseen email in raw form */

/* void FetchHeaders( CURL *curl, CURLcode res, int msgID );  Fetch Header Fields "Subject", "From" */
void FetchUnseenNotMixed( CURL *curl, CURLcode res, int msgID); /* Fetch Unseen email actual data */
void FetchUnseenMixed( CURL *curl, CURLcode res, int msgID); /* Fetch email which has attachments */


void decode(char *fromFile, char *toFile);
void Text2Speak(char *fromFile);


int fetchEmail(char *email, char *password);



 /* int main()
{

 char *email="kokotest94@gmail.com";
 char *pass="testgmail";

//printf("Email:%s\nPass:%s\n",email,pass);
 
 fetchEmail(email,pass);


} */





int fetchEmail(char *email, char *password)
{

    char cwd[1024];

    getcwd(cwd, sizeof(cwd)); /* get current working directory */



  CURL *curl;
  CURLcode res = CURLE_OK;

  curl = curl_easy_init();
  if(curl) {
    /* Set username and password */
   // curl_easy_setopt(curl,CURLOPT_CAPATH,"/etc/ssl/certs/");

    curl_easy_setopt(curl, CURLOPT_USERNAME, email);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password);

   curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4); /* Use IPv4 only, becasue IPv6 usually have problems */

   char *homedir;
   homedir=getenv("HOME"); /* it returns /home/cucu */
   char CertificatePath[300];
   sprintf(CertificatePath,"%s/Desktop/e4vip/Fetch/gmail-cert-imap.pem",homedir);
   curl_easy_setopt(curl, CURLOPT_CAINFO, CertificatePath);

    /* This will fetch message 1 from the user's inbox. Note the use of
    * imaps:// rather than imap:// to request a SSL based connection. */



/* ******************************************************************************
   *                                                                            *
   *                   Perform the whole operation                              *
   *                                                                            *
   ******************************************************************************         */


    SearchUnseen(curl, res);
    int MSGid;
    if( isUnseenAvailable() )
       {
         
         MSGid=SearchMSGid();

         FetchUnseenRaw(curl,res,MSGid);
         
         if( isTextPlain("fetchedEmailRaw.txt") && !isAudioMpeg("fetchedEmailRaw.txt") && !isMultipartMixed("fetchedEmailRaw.txt") && !isAudioXWav("fetchedEmailRaw.txt") )
            {
               FetchUnseenNotMixed(curl,res,MSGid); /* fetch Section=1 */
           
               printf("Found as TextPlain\n");
             if( isEncoded("fetchedEmailRaw.txt") )
                 {
                     
               
                    decode("fetchedEmail.txt","fetchedPlainText.txt"); //decode the email to plaintex 
                    char confirm='n'; // Default repeat 
                    while( confirm != 'q' && confirm != 'Q' ) 
                        { 
                            char *Subject=getSubject("fetchedEmailRaw.txt");
                            char *From=getFrom("fetchedEmailRaw.txt");
                            char query[256];
                            
                            sprintf(query,"~/Desktop/e4vip/pico2wave.sh \"You have a new email from %s with \
                            a subject line %s . The email read as follows.\"",From,Subject);
                            
                            system(query);
                            
                            Text2Speak("fetchedPlainText.txt"); /* read the email */ 

                            system("~/Desktop/e4vip/pico2wave.sh \"To listen to your email again Enter Y or \
                            Q to skip\"");
                            scanf(" %c", &confirm);  /* The %c specifier doesn't skip blanks,tabs 
                            etc so an extra space/blank is added */ 
                         
                           }
                   
                   }
              else if( !isEncoded("fetchedEmailRaw.txt") )
                  {  
             
                        /* if email is not encoded, but a plain english text */ 
                         char confirm='n'; /* Default repeat */ 
                         while( confirm != 'q' && confirm != 'Q' )
                          { 
                            char *Subject=getSubject("fetchedEmailRaw.txt");
                            char *From=getFrom("fetchedEmailRaw.txt");
                            char query[256];
                            
                            sprintf(query,"~/Desktop/e4vip/pico2wave.sh \"You have a new email from %s with \
                            a subject line %s . The email read as follows.\"",From,Subject);
                            
                            system(query); 
                            
                            Text2Speak("fetchedEmail.txt"); /* read the email */

                            system("~/Desktop/e4vip/pico2wave.sh \"To listen to your email again Enter Y or \
                            Q to skip\"");
                            scanf(" %c", &confirm); /* The %c specifier doesn't skip blanks,tabs 
                            etc so an extra space/blank is added */ 
                         
                           }
                        
                   
                   } 
              
          
             }
         else if( isAudioWav("fetchedEmailRaw.txt") || isAudioXWav("fetchedEmailRaw.txt") )
            {
                    FetchUnseenMixed(curl,res,MSGid);
                    printf("AudioWav and AudioXWav block is executed\n");

                    decode("fetchedEmail.txt","recievedmail.wav"); /* decode the email to wav form */
                    char confirm='n'; /* Default */ 
                    while( confirm != 'q' && confirm != 'Q' ) 
                        { 
                            char *Subject=getSubject("fetchedEmailRaw.txt");
                            char *From=getFrom("fetchedEmailRaw.txt");
                          
                            
                          /* using const string to avoid remote code execution */
                           
                         const char shellScript[] = "~/Desktop/e4vip/pico2wave.sh \"You have a new email from $From with a subject line   $Subject\" The email read as follows.";

                      /*then, after we have a subject, we can set them in the environment */
                        if(setenv("Subject", Subject, 1) == 0 && setenv("From", From, 1) == 0) {
                        system(shellScript);
                        unsetenv("Subject"); /* avoid leaking data to other parts or children 
                        of    your program  */
                       unsetenv("From");
                       } 
                     else {  /* setenv failed -- maybe we were run with a very full environment? */
                     /* (or maybe the remote user provided a too-large Subject or From) */
                      
                       exit(1); 
                       }
                        
                        /* Alternatively:
                           
                           char query[256];
                            printf("Subject: %s\n From: %s\n",Subject,From);
                            sprintf(query,"./pico2wave.sh \"You have a new email from %s with \
                            a subject line %s .The email read as follows.\"",From,Subject);
                           
                          ... and then use system(query) 
                         */
                            
                            system("aplay recievedmail.wav");

                            system("~/Desktop/e4vip/pico2wave.sh \"To listen to your email again Enter Y or Q to skip\"");
                            scanf(" %c", &confirm);  /* The %c specifier doesn't skip blanks,tabs 
                            etc so an extra space/blank is added */ 
                         
                           }               


             
             
             }
         else if( isAudioMp3("fetchedEmailRaw.txt") || isAudioMpeg("fetchedEmailRaw.txt") )
            {
                    FetchUnseenMixed(curl,res,MSGid);

                    decode("fetchedEmail.txt","recievedmail.mp3"); /* decode the email to wav form */
                    char confirm='n'; /* Default */ 
                    while( confirm != 'q' && confirm != 'Q' ) 
                        { 
                            char *Subject=getSubject("fetchedEmailRaw.txt");
                            char *From=getFrom("fetchedEmailRaw.txt");
                            char query[256];
                            
                            sprintf(query,"~/Desktop/e4vip/pico2wave.sh \"You have a new email from %s with \
                            a subject line %s .The email read as follows.\"",From,Subject);
                            
                            system(query);
                            
                            system("mpg123 recievedmail.mp3"); /* mpg123 is a tool to play mp3 files */

                            system("~/Desktop/e4vip/pico2wave.sh \"To listen to your email again Enter Y or Q to skip\"");
                            scanf(" %c", &confirm);  /* The %c specifier doesn't skip blanks,tabs 
                            etc so an extra space/blank is added */ 
                         
                           }               



             
             }
          else
             {
               system("~/Desktop/e4vip/pico2wave.sh \"Unknown email contents\"");
               exit(0);  
              }




         }
    else
        { 
          system("~/Desktop/e4vip/pico2wave.sh \"No new email is available, Please check again later\"");
          exit(0); /* Sorry there is no new emails available */

         }
    
    
    



/* ******************************************************************************
   *                                                                            *
   *                   End of the whole operation                               *
   *                                                                            *
   ******************************************************************************         */



    /* If you have a CA cert for the server stored someplace else than in the
     * default bundle, then the CURLOPT_CAPATH option might come handy for
     * you. */
      
#ifdef SKIP_PEER_VERIFICATION
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

    /* If the site you're connecting to uses a different host name that what
     * they have mentioned in their server certificate's commonName (or
     * subjectAltName) fields, libcurl will refuse to connect. You can skip
     * this check, but this will make the connection less secure. */
#ifdef SKIP_HOSTNAME_VERIFICATION
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif

    /* Since the traffic will be encrypted, it is very useful to turn on debug
     * information within libcurl to see what is happening during the
     * transfer */
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

   /* FILE *filetoWrite; /* open a file to write the fetched data to */
   //filetoWrite=fopen("fetched.txt","w");
   
   // curl_easy_setopt(curl, CURLOPT_WRITEDATA, filetoWrite); /* write recieved/fetched data to the file opened for writing */

    /* Perform the fetch */
    //res = curl_easy_perform(curl);

    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* Always cleanup */
    curl_easy_cleanup(curl);
  }

  return (int)res;
}


void SearchUnseen(CURL *curl, CURLcode res)
 {
    
 curl_easy_setopt(curl, CURLOPT_URL,"imaps://imap.gmail.com:993/INBOX?UNSEEN");

  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); /* Turn debug information ON */

 FILE *filetoWrite2; /* open a file to write the fetched data to */
   filetoWrite2=fopen("UnseenIDs.txt","w");
   
   curl_easy_setopt(curl, CURLOPT_WRITEDATA, filetoWrite2); /* write recieved/fetched data to the file opened for writing */

   res = curl_easy_perform(curl); /* Perform the operation */
    //curl_easy_cleanup(curl);

   fclose(filetoWrite2); /* close opened file */



 }



void FetchUnseenNotMixed( CURL *curl, CURLcode res, int msgID)
 {
/* This function will fetch those unseen emails which has their Content-Type: multipart/alternative which usually have encoded text or plain/text or html/text and have no attachments, and that's why we will fetch the 1st Section of the email */
 
char customURL[100];
sprintf(customURL,"imaps://imap.gmail.com:993/INBOX;UID=%i;SECTION=1", msgID); 


//sprintf(customURL,"imaps://imap.gmail.com:993/INBOX;UID=%i;SECTION=HEADER.FIELDS%%20(Subject%%20From%%20Conten-Transfer-Encoding)", msgID);

  curl_easy_setopt(curl, CURLOPT_URL,customURL);


  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); /* Turn debug information ON */

  FILE *filetoWrite2; /* open a file to write the fetched data to */
  filetoWrite2=fopen("fetchedEmail.txt","w");
   
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, filetoWrite2); /* write recieved/fetched data to the file opened for writing */

    /* Perform the fetch */
    res = curl_easy_perform(curl);
 
    fclose(filetoWrite2); /* close opened file */


 }



void FetchUnseenMixed( CURL *curl, CURLcode res, int msgID)
 {
/* This function will fetch those unseen emails which has their Content-Type: multipart/mixed which usually have encoded attachments like mp3,wav or mpeg and could also have text/plain etc that's why we have to fetch the 2nd Section of the email */
 
char customURL[100];
sprintf(customURL,"imaps://imap.gmail.com:993/INBOX;UID=%i;SECTION=2", msgID); 


//sprintf(customURL,"imaps://imap.gmail.com:993/INBOX;UID=%i;SECTION=HEADER.FIELDS%%20(Subject%%20From%%20Conten-Transfer-Encoding)", msgID);

  curl_easy_setopt(curl, CURLOPT_URL,customURL);


  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); /* Turn debug information ON */

  FILE *filetoWrite2; /* open a file to write the fetched data to */
  filetoWrite2=fopen("fetchedEmail.txt","w");
   
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, filetoWrite2); /* write recieved/fetched data to the file opened for writing */

    /* Perform the fetch */
    res = curl_easy_perform(curl);
 
    fclose(filetoWrite2); /* close opened file */


 }










void FetchUnseenRaw( CURL *curl, CURLcode res, int msgID )
 {

char customURL[100];
sprintf(customURL,"imaps://imap.gmail.com:993/INBOX;UID=%i", msgID); 

  curl_easy_setopt(curl, CURLOPT_URL,customURL);


  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); /* Turn debug information ON */

  FILE *filetoWrite2; /* open a file to write the fetched data to */
  filetoWrite2=fopen("fetchedEmailRaw.txt","w");
   
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, filetoWrite2); /* write fetched raw data to the file opened for writing */

    /* Perform the fetch */
    res = curl_easy_perform(curl);
 
    fclose(filetoWrite2); /* close opened file */


  }



/* Not needed now 

void FetchHeaders( CURL *curl, CURLcode res, int msgID )
 {
   char customURL[100];
   sprintf(customURL,"imaps://imap.gmail.com:993/INBOX;UID=%i;SECTION=HEADER.FIELDS%%20(From%%20Subject)", msgID); 

   curl_easy_setopt(curl, CURLOPT_URL,customURL);


   curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); // Turn debug information ON 
 
   FILE *filetoWrite2; // open a file to write the fetched data to 
   filetoWrite2=fopen("fetchedHeaders.txt","w");
   
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, filetoWrite2); // write fetched raw data to the file opened for writing 

    // Perform the fetch 
    res = curl_easy_perform(curl);
 
    fclose(filetoWrite2); // close opened file 


   } 
     */



void decode(char *fromFile, char *toFile)
 {
    
   /* decode the base64 text from file "fetchedEmail.txt" to file "fetchedPlainText.txt" */
   char query[100];
   sprintf(query,"openssl base64 -d -in %s -out %s",fromFile,toFile);
  

   system(query);

 }

void Text2Speak(char *fromFile)
 {
   /* speak the plain text from file "fetchedPlainText.txt" */

   char query[100];
   sprintf(query,"~/Desktop/e4vip/pico2wave.sh \"$(cat %s)\"",fromFile);
   
   system(query);
  
 }






/* If file is empty then no need to decode it or if decoding fails then it means
   it is already a plain text file and doesn't need decoding.
 */


