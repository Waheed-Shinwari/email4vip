#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <stdbool.h>
#include<stdlib.h>
#include<regex.h>

bool isEmail( const char *email);
bool isAuthentic_SMTP(char *email, char *password);
bool isAuthentic_IMAP(char *email, char *password);


/* int main(void)
{

char *email="kokotest94@gmail.com";
char *pass = "testgmail";

printf("is email format correct: %d\n",isEmail(email) );
printf("is SMTP email authentic: %d\n",isAuthentic_SMTP(email,pass) );
printf("is Imap email authentic: %d\n",isAuthentic_IMAP(email,pass) );

 } */


bool isEmail( const char *email)
{
/*
 * Match string against the extended regular expression in
 * pattern to see if a the email is a valid address, treating errors as no match.
 *
 * Return 1 for match, 0 for no match.
 */


    char *pattern="[a-z0-9!#$%&'*+/=?^_`{|}~-]+(\\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*@([a-z0-9]([a-z0-9-]*[a-z0-9])?\\.)+[a-z0-9]([a-z0-9-]*[a-z0-9])?";

    
    int    status;
    regex_t    re;

    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
        return(0);      /* Report error. */
    }
   
    status = regexec(&re, email, (size_t) 0, NULL, 0);
    regfree(&re);
    if (status != 0) {
        return(0);      // Report error
    }
 
   return(1);
 
  
   }



bool isAuthentic_SMTP(char *email, char *password)
 {
      /* if error returned is 0 then it is authentic or if the error "Login denied" is
           returned then the email and pass are not authentic */

   bool status;

  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl) {
    /* This is the URL for your mailserver */
    curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587");
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
 
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
    curl_easy_setopt(curl, CURLOPT_USERNAME, email);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password);

   char *homedir;
   homedir=getenv("HOME"); /* it returns /home/cucu */
   char CertificatePath[300];
   sprintf(CertificatePath,"%s/Desktop/e4vip/Send/gmail-cert-smtp.pem",homedir);
   curl_easy_setopt(curl, CURLOPT_CAINFO, CertificatePath);


    /* Perform the VRFY */
    res = curl_easy_perform(curl);

    /* Check for errors */
    if(res != CURLE_OK && !strcmp("Login denied",curl_easy_strerror(res)) )
     {
        //fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
       //printf("error is: %s\n",curl_easy_strerror(res));
       //printf("Login denied code is: %d\n",res);
            status=0;
          
      }
     else if (res == CURLE_OK)
      {
        status=1; /* everything is ok */
       }


    curl_easy_cleanup(curl);
     }
 
 return status;


  }


bool isAuthentic_IMAP(char *email, char *password)
 {
      /* if error returned is 0 then it is authentic or if the error "Login denied" is
           returned then the email and pass are not authentic */

   bool status;

  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl) {
    /* This is the URL for your mailserver */
    curl_easy_setopt(curl, CURLOPT_URL, "IMAPS://imap.gmail.com:993");
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
 
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
    curl_easy_setopt(curl, CURLOPT_USERNAME, email);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password);

   char *homedir;
   homedir=getenv("HOME"); /* it returns /home/cucu */
   char CertificatePath[300];
   sprintf(CertificatePath,"%s/Desktop/e4vip/Fetch/gmail-cert-imap.pem",homedir);
   curl_easy_setopt(curl, CURLOPT_CAINFO, CertificatePath);


    /* Perform the VRFY */
    res = curl_easy_perform(curl);

    /* Check for errors */
    if(res != CURLE_OK && !strcmp("Login denied",curl_easy_strerror(res)) )
     {
        //fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
       //printf("error is: %s\n",curl_easy_strerror(res));
       //printf("Login denied code is: %d\n",res);
            status=0;
          
      }
     else if (res == CURLE_OK)
      {
        status=1; /* everything is ok */
       }


    curl_easy_cleanup(curl);
     }
 
 return status;


  }


