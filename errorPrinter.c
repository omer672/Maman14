#include "errorPrinter.h"

void getErrorMessage(StatusCode code,char* message)
{ /* Tal, add error messages in this format */
    switch (code) {
    case success:
        break;
    case wrong_number_of_operands:
        strcpy(message,"Wrong number of operands");
        break;
    case unrecognized_command:
        strcpy(message,"Unrecognized command");
        break;
    case illigal_symbol_name:
        strcpy(message,"Illigal symbol name");
        break;
    case redeclaration_of_symbol:
        strcpy(message,"Symbol already exist");
        break;
    case symbol_doesnt_exist:
        strcpy(message,"Symbol doesn't exist");
        break;
    case data_syntax_error:
        strcpy(message,".data syntax error");
        break;
    case string_syntax_error:
        strcpy(message,".string syntax error");
        break;
    case struct_syntax_error:
        strcpy(message,".struct syntax error");
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
