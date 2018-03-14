#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "main.h"
#include "LinkedList.h"
#include "helper.h"
#include <ctype.h>

StatusCode setSymbol(char* name,int value,char* mark,Types type);

Symbol* getHead();
Symbol* doesExist(char* name);

#endif
