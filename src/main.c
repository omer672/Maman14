#include "main.h"

/*Global variables*/
char* instructions[] = {"mov", "cmp", "add", "sub", "lea","not","clr","inc","dec", "jmp", "bne", "red", "prn", "jsr","rts", "stop"};
char* dataTypes[] = {"data","string","struct"};
char* registers[] = {"r0","r1","r2","r3","r4","r5","r6","r7"};
int dataArray[MAX_FILE_LENGTH];
int instructionsArray[MAX_FILE_LENGTH];
int DC,IC;
int entryFound = 0;
int externFound = 0;
int errorsFound = 0;

void iterate(FILE*, char*);

void clearGlobals();

void runProg(char* fileName)/*main function for running the Assembler*/
{
    FILE* file;
    char fileFullName[MAX_FILE_LENGTH+3];
    strcpy(fileFullName,fileName);
    strcat(fileFullName,".as");
    if((file = fopen(fileFullName,"r")) != NULL)
    {
        clearGlobals();
        iterate(file,fileName);
    }
    else
        fprintf(stderr,"File cannot be open, moving on. %s",fileFullName);
}

int main(int argc, char *argv[])
{
    int i;
    for(i = 1; i < argc; i++)
    {
        runProg(argv[i]);
    }
    return 0;
}



