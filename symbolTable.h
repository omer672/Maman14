#ifndef __symbolTable_h__
 #define __symbolTable_h__

#include "main.h"
#include "LinkedList.h"
#include "helper.h"
#include <ctype.h>

typedef enum type { external,relocatable } Types;
typedef struct symbol
{
    char* name;
    char* value;
    char* mark;
    Types type;
    struct symbol next;
} Symbol;

int setSymbol(char* name,char* value,char* mark,Types type);

#endif  __symbolTable_h__
