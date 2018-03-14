#include "errorPrinter.h"

void getErrorMessage(StatusCode code,char* message)
{ /* Tal, add error messages in this format */
    switch (code) {
    case success:
        break;
    case wrong_number_of_operands:
        strcpy(message,"Wrong number of operands");
        break;
    }
}


void printError(StatusCode code, int line, char* fileName)
{
    char errorMessage[MAX_FILE_LENGTH];
    if(code<0)
    {
        getErrorMessage(code,errorMessage);
        fprintf(stderr,"Error: %s. On line: %d and file: %s",errorMessage,line,fileName);
    }
}
