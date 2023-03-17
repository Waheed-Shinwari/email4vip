#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef  _HEADPHONE_STATUS_H_ 
#define  _HEADPHONE_STATUS_H_ 

char *extractRequiredLine();

char *computeStatus(char *extractedLine);

void start_checking_headphone_status(void);

#endif

