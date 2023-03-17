#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <curl/curl.h>

void prepend(char* payload_text, const char* emailFormat); /* To append str2 to the start of str1 */
void CreateEmailFile(char *From, char *To, char *Subject); /* Generate email format with from attachment */

int sendEmail(char *MyEmailID, char *password, char *Reciever,char *Subject);


/*
int main(void)
 {

 sendEmail("kokotest94@gmail.com","testgmail","kokotest94@gmail.com","Last and Final");




 } */





int sendEmail(char *MyEmailID, char *password, char *Reciever,char *Subject)
 {


  CreateEmailFile(MyEmailID,Reciever,Subject); /* First create the email formated file */

  CURL *curl;
  CURLcode res = CURLE_OK;
  struct curl_slist *recipients = NULL;

  curl = curl_easy_init();
  if(curl) {
    // This is the URL for your mailserver 
    curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587");
    
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
    curl_easy_setopt(curl, CURLOPT_USERNAME, MyEmailID);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password);


  curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4); // Use IPv4 only, becasue IPv6 usually have problems 

   char *homedir;
   homedir=getenv("HOME"); /* it returns /home/cucu */
   char CertificatePath[300];
   sprintf(CertificatePath,"%s/Desktop/e4vip/Send/gmail-cert-smtp.pem",homedir);
   curl_easy_setopt(curl, CURLOPT_CAINFO, CertificatePath);

   curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); // To see debug information 



    /* Note that this option isn't strictly required, omitting it will result
     * in libcurl sending the MAIL FROM command with empty sender data. All
     * autoresponses should have an empty reverse-path, and should be directed
     * to the address in the reverse-path which triggered them. Otherwise,
     * they could cause an endless loop. See RFC 5321 Section 4.5.5 for more
     * details.
     */
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, MyEmailID); /* From: MyEmailID */

    /* Add two recipients, in this particular case they correspond to the
     * To: and Cc: addressees in the header, but they could be any kind of
     * recipient. */
    recipients = curl_slist_append(recipients, Reciever); /* TO: Reciever */
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

    FILE *file2upload=fopen("FormatedEmail.txt","r");
    

    /* We're using a callback function to specify the payload (the headers and
     * body of the message). You could just use the CURLOPT_READDATA option to
     * specify a FILE pointer to read from. */
    //curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
    curl_easy_setopt(curl, CURLOPT_READDATA, file2upload);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

    // Send the message 
    res = curl_easy_perform(curl);

    // Check for errors 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    // Free the list of recipients 
    curl_slist_free_all(recipients);

    /* curl won't send the QUIT command until you call cleanup, so you should
     * be able to re-use this connection for additional messages (setting
     * CURLOPT_MAIL_FROM and CURLOPT_MAIL_RCPT as required, and calling
     * curl_easy_perform() again. It may not be a good idea to keep the
     * connection open for a very long time though (more than a few minutes
     * may result in the server timing out the connection), and you do want to
     * clean up in the end.
     */
    curl_easy_cleanup(curl);
  
    }

  return (int)res; 

  }




void CreateEmailFile(char *From,char *To,char *Subject)
 {

 /* This function convert the recorded media file into base64 text, and then create a email compatable file which can be then uploaded to an smtp server or sent as an email with voicemail.wav as a attachment file. */

 char *payload_text =NULL;
 char emailFormat[800];

 sprintf(emailFormat,"From: %s\nSubject: %s\nTo: %s\n\
User-Agent: e4vip email\n-e MIME-Version: 1.0 (mime-construct 1.9)\n\
Content-Type: multipart/mixed; boundary=\"001a113c265622702c0557ace7f8\"\n\n\
--001a113c265622702c0557ace7f8\nContent-Type: multipart/alternative; boundary=\"001a113c26562270250557ace7f6\"\n\n--001a113c26562270250557ace7f6\nContent-Type: text/plain; charset=\"UTF-8\"\n\n\n\n--001a113c26562270250557ace7f6\nContent-Type: text/html; charset=\"UTF-8\"\n\n<div dir=\"ltr\"><br></div>\n\n--001a113c26562270250557ace7f6--\n--001a113c265622702c0557ace7f8\nContent-Type: audio/x-wav; name=\"voicemail.wav\"\nContent-Disposition: attachment; filename=\"voicemail.wav\"\nContent-Transfer-Encoding: base64\n\n",From,Subject,To);

       
 system("openssl base64 -in voicemail.wav -out voicemailBase64.txt");


 FILE *fp = fopen("voicemailBase64.txt", "r");
 if (fp != NULL) 
 {
    /* Go to the end of the file. */
    if (fseek(fp, 0L, SEEK_END) == 0) 
    {
        /* Get the size of the file. */
        long bufsize = ftell(fp);
        if (bufsize == -1) 
        { /* Error */ }

        /* Allocate our buffer to that size. */
        payload_text = malloc(sizeof(char) * (bufsize + 40+strlen(emailFormat)));

        /* Go back to the start of the file. */
        if (fseek(fp, 0L, SEEK_SET) != 0) 
        { /* Error */ }

        /* Read the entire file into memory. */
        size_t newLen = fread(payload_text, sizeof(char), bufsize, fp);
        if ( ferror( fp ) != 0 ) {
            fputs("Error reading file", stderr);
        } 
        else {
           payload_text[newLen++] = '\0'; /* Just to be safe. */
            }
    }
    fclose(fp);
   
   prepend(payload_text, emailFormat); /* Add emailFormat to the start of the Payload_Text */
   strcat(payload_text,"--001a113c265622702c0557ace7f8--"); /* close the boundry of multipart/mixed */

  }

 /* generate the final formated file to be uploaded*/
 FILE *finalFile=fopen("FormatedEmail.txt","w"); 
 fwrite(payload_text,sizeof(char),strlen(payload_text),finalFile);

 free(payload_text); /* Don't forget to call free() later! */ 
 
 fclose(finalFile);

 }




void prepend(char* payload_text, const char* emailFormat) 
{   
      /* Prepends "emailFormat" into "payload_text". 
      Assumes "payload_text" has enough space
      allocated for the combined string. */

    /* Add emailFormat to the Begening of the payload_text */
    size_t len = strlen(emailFormat);
    size_t i;
    
    /* memmove() to shift the original string by the length of what you want to prepend and then  
    copy that one into the beginning */
    memmove(payload_text + len, payload_text, strlen(payload_text) + 1);

    for (i = 0; i < len; ++i)
    {
        payload_text[i] = emailFormat[i];
    }
  
  }













