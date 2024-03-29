/*    This file defines two functions, one to extract the required line from the file
      generated by the grep command: 
        "grep Pin-Ctls /proc/asound/PCH/codec#0 > headphone-status.info" 
      and then compute or extract the haaphone status value from the the extracted line */


#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"headphone-status.h"


char *extractRequiredLine();
char *computeStatus(char *extractedLine);

extern char *extractedLineN;



char *extractRequiredLine()
   {
		
/* First we execute the "grep" command to find the pattern or check the status
   of the headphone on the sound card file.
   and redirect the results to a file "headphone-status.info" */
system("grep Pin-ctls /proc/asound/PCH/codec#0 > headphone-status.info");

/* Now we have to extract the required results i.e only the headphone status from the
   "headphone-status.info" file. */



static const char filename[] = "headphone-status.info";
FILE *file = fopen(filename, "r");
int newLineCount = 0;
int RequiredLineNumber = 1;
static char extractedLine[256];    /* static , otherwise local varialble will lose data */
  if ( file != NULL )
   {
       
    while (fgets(extractedLine, sizeof extractedLine, file) != NULL) /* read a line */
    {
        if (newLineCount == RequiredLineNumber)
        {
	   
            break;
        }
        else
        {
            newLineCount++;
        }
    }
    fclose(file);
                       }
 else
   {
          //file doesn't exist
           }
  
  return extractedLine;

	                 }    /* END of extractRequiredLine() */


/* Start of computeStatus() */
char *computeStatus(char *extractedLine)
{
	char *status;
	if( ( strpbrk(extractedLine,"OUT") ) != NULL)  /* search for OUT or else put IN */
		{
		      status="OUT";
			}
	else if( (strpbrk(extractedLine,"OUT")) == NULL)
		{
		      status="IN";
			}
	return status; 
  
				
 }  /* END of computeStatus() */


