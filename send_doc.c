#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include <sys/types.h>
#include <curl/curl.h>


int isDirEmpty(char *dirName);
char *getDocName( char *dirName);

void CreateEmailFile(char *From,char *To,char *Subject);
void prepend(char* payload_text, const char* emailFormat);

int sendDocEmail(char *MyEmailID, char *password, char *Reciever,char *Subject);

int main(void)
{

//printf("Dir entries: %d\n",isDirEmpty("send_doc"));
//printf("File is: %s\n",getDocName("send_doc") );


sendDocEmail("kokotest94@gmail.com","testgmail","kokotest94@gmail.com","Hello dot ODT");







 }

 
  
int sendDocEmail(char *MyEmailID, char *password, char *Reciever,char *Subject)
 {
 
 CreateEmailFile(MyEmailID,Reciever,Subject); /*First create the email formated file*/
  
  
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

 char *odtFileName=getDocName("./send_doc");

 char *payload_text =NULL;
 char emailFormat[900];

 sprintf(emailFormat,"From: %s\nSubject: %s\nTo: %s\n\
User-Agent: e4vip email\n-e MIME-Version: 1.0 (mime-construct 1.9)\n\
Content-Type: multipart/mixed; boundary=\"94eb2c11465a22e5c9055899e22f\"\n\n\
--94eb2c11465a22e5c9055899e22f\nContent-Type: multipart/alternative; boundary=\"94eb2c11465a22e5bd055899e22d\"\n\n--94eb2c11465a22e5bd055899e22d\nContent-Type: text/plain; charset=\"UTF-8\"\n\n\n\n--94eb2c11465a22e5bd055899e22d\nContent-Type: text/html; charset=\"UTF-8\"\n\n<div dir=\"ltr\"><br></div>\n\n--94eb2c11465a22e5bd055899e22d--\n--94eb2c11465a22e5c9055899e22f\nContent-Type: application/vnd.oasis.opendocument.text; name=\"%s\"\nContent-Disposition: attachment; filename=\"%s\"\nContent-Transfer-Encoding: base64\n\n",From,Subject,To,odtFileName,odtFileName);


 char query[256];     
 sprintf(query,"openssl base64 -in ./send_doc/%s -out odtBase64.txt",odtFileName); 
 system(query);


 FILE *fp = fopen("odtBase64.txt", "r");
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
   strcat(payload_text,"--94eb2c11465a22e5c9055899e22f--"); /* close the boundry of multipart/mixed */

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


int isDirEmpty(char *dirName)
 {
    
     int status=0;


        int n=0;
        struct dirent* d;

        DIR* dir = opendir(dirName);
        if (dir == NULL) /* Not a directory or doesn't exist */
        return 0;

        while((d = readdir(dir))!=NULL) 
        {
           n++;
           }
        closedir(dir);
        
    if( n<=2 ) /* if only 2 entries in the dir */
      {
         status=0; /* dir is empty */
       }
    else  /* else if 3 or more entries */
       {
         status=1; /* then dir isn't empty */

        }

        return status;

 
/* Historically, the first Unix filesystem created two entries in every directory: . 
   pointing to the directory itself, and .. pointing to its parent. This provided an easy way to
  traverse the filesystem, both for applications and for the OS itself.

  Thus each directory has a link count of 2+n where n is the number of subdirectories. 
  The links are the entry for that directory in its parent, the directory's own . entry, 
  and the .. entry in each subdirectory.

  Later filesystems have tended to keep track of parent directories in memory and 
  usually don't need . and .. to exist as actual entries; typical modern unix systems 
  treat . and .. as special values as part of the filesystem-type-independent filesystem code.
  Some filesystems still include . and .. entries, or pretend to even though nothing appears 
  on the disk.

  Most filesystems still report a link count of 2+n for directories regardless of 
  whether . and .. entries exist, but there are exceptions, for example btrfs doesn't do this.

 
  */

  }


char *getDocName( char *dirName)
 {

    DIR   *dir;
    static char *docFileName;
    struct dirent *d;

    dir = opendir(dirName);
    if (dir)
      {
         while ((d = readdir(dir)) != NULL)
          {
            
            if (d->d_type == DT_REG) /* if its a regular file and not "." or ".." entry */
               {
                 //printf("%s\n", d->d_name);
                 docFileName = d->d_name;
                 //docFileName[strlen(docFileName)-1]='\0';
                }
         
          
            }

    closedir(dir);
       }
     
      return docFileName;


 }











