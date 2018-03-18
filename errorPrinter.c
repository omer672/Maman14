#include "errorPrinter.h"
/*The function handles all errors and print suitable notice*/
void getErrorMessage(StatusCode code,char* message)
{
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
    case symbol_not_recognized:
        strcpy(message,"symbol not recognized error");
        break;
    case operand_type_error:
        strcpy(message,"operand type error");
        break;
    case row_count_error:
        strcpy(message,"counting summary of rows error");
        break;
    case inst_sum_error:
        strcpy(message,"instruction rows summary error");
        break;
    case invalid_source_dest_operands:
        strcpy(message,"Invalid source or destination operands");
        break;
    }
}

/*The function will print the error with the line error appeared*/
void printError(StatusCode code, int line, char* fileName)
{
    char errorMessage[MAX_FILE_LENGTH];
    if(code<0)
    {
        getErrorMessage(code,errorMessage);
        fprintf(stderr,"Error: %s. On line: %d and file: %s\n",errorMessage,line,fileName);
    }
}
