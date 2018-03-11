#include "main.h"
/*Operation codes - each one will parse to his binary 4 code*/
typedef enum opCode{mov, cmp, add, sub, not, clr, lea, inc, dec, jmp, bne, red, prn, jsr, rts, stop};
char* opCodes[16]={"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop"};
/*Im - 00, Direct=01, Struct=10, register=11*/
typedef enum { Immediate = 0, Direct, Struct, Register}opType;
int isInstuction(char* string);

int isDataType(char* string);

int isRegister(char* string);

int isExtern(char* string);

int isEntry(char* string);

void insertData(char* type, char *data);

void insertExtern(char* symbols);

void insertInstruction(char* instruction, char* operands, int isSecondIteration);
