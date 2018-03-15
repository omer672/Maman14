#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 80 /*Max line length*/
#define NUM_OF_INSTRUCTS 16
#define NUM_OF_DATA_TYPES 3
#define NUM_OF_REGISTERS 8
#define MAX_SYMBOL_LEN 30
#define MAX_PARAMS 3
#define MAX_DIGITS 12
#define START_ADDRESS 100
#define MAX_FILE_LENGTH 256
#define EXTERN "extern"
#define ENTRY "entry"

/*TODO: FIX ALL STRCMP - when it returns 0 means both strings are equal */

typedef enum type { external,relocatable } Types;
typedef struct symbol
{
    char name[MAX_SYMBOL_LEN];
    int value;
    int wasGivenAtData;
    int isEntry;
    Types type;
    struct symbol* next;
} Symbol;

typedef enum errorList {
    success = 0,
    wrong_number_of_operands = -1,
    unrecognized_command = -2,
    illigal_symbol_name = -3,
    redeclaration_of_symbol = -4,
    symbol_doesnt_exist = -5,
    data_syntax_error = -6,
    string_syntax_error = -7,
    struct_syntax_error = -8

    /* Tal add any errors you need in this format (decsending numbers) */
} StatusCode;

typedef enum opCode { mov, cmp, add, sub, not, clr, lea, inc, dec, jmp, bne, red, prn, jsr, rts, stop } OpCodes;

/*Im - 00, Direct=01, Struct=10, register=11*/
typedef enum types { Immediate = 0, Direct, Struct, Register} opType;

extern char* instructions[NUM_OF_INSTRUCTS];
extern char* dataTypes[NUM_OF_DATA_TYPES];
extern char* registers[NUM_OF_REGISTERS];
extern int dataArray[MAX_FILE_LENGTH];
extern int instructionsArray[MAX_FILE_LENGTH];
extern int DC,IC;
extern int errorsFound;

void runProg(char* fileName);

#endif
