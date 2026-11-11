#ifndef IO_H
#define IO_H


char * getFileName(char* inputFileName);
char * getFromFile(char targetArray[], int* targetLengthAddr);
char * getFromUser(char targetArray[], int* targetLengthAddr);
int saveToFile(char outputArray[]);


#endif
