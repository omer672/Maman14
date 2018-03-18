#ifndef HELPER_H
#define HELPER_H
#define FIRST_INSTRUCTION_GROUP_INDEX 4
#define SECOND_INSTRUCTION_GROUP_INDEX 13

#include "main.h"
#include "symbolTable.h"
#include "Parsing.h"
#include "commandsToBinary.h"

/*The function checks if string inserted to the function is an Instruction*/
int isInstuction(char* string);

/*The functions checks if string inserted is a data type by definition*/
int isDataType(char* string);

/*The function checks if string inserted is a register(r0..r7)*/
int isRegister(char* string);

/*The function checks if string inserted is a extern by definition*/
int isExtern(char* string);

/*The function checks for white spaces on line inserted*/
int isWhitespace(char* line);

/*The function check if string inserted to the function is int by definition*/
int isInt(char* string);

/*The function checks if string entered to function is an entry by definition*/
int isEntry(char* string);

/*The function handles .data .string .struct type and inserts it to dataArray. Handles DC.*/
StatusCode insertData(char* type, char *data);
/*The function handles .extern type and inserts it to the symbol table, marking it accordingly */
StatusCode insertExtern(char* symbols);

/*The function gets instruction, operands, checks if first or second iterate and handles instruction Array (enters Binary code)
 * Handles errors through edge cases that could appeared on line */
StatusCode insertInstruction(char* instruction, char* operands, int isSecondIteration);

#endif
