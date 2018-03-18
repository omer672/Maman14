#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "main.h"
#include "LinkedList.h"
#include "helper.h"
#include <ctype.h>

/*The function gets pointer to symbol and checks if the name is legal.
 * Case legal - success
 * case illegal - returns error*/
StatusCode isLegal(char* symbol);

/*The function gets new symbol variables and checks if legal. case legal - adds a new symbol. else - prints error*/
StatusCode setSymbol(char* name,int value,SymbolType sType,int isEntry, Types type);

/*The function returns the head of symbols list*/
Symbol* getHead();

/*The function gets name of symbol and search if its already exists on symbol list
 * Input: symbol name
 * Output: pointer to symbol of found*/
Symbol* doesExist(char* name);

Symbol* doesStructExist(char* name);

/**/
void updateDataSymbolValues(int value);

/*The function will free a linked list of symbols from allocated memory*/
void freeSymbolTable();


#endif
