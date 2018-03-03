#include "symbolTable.h"

Symbol* head = NULL;

int setSymbol(char* name,char* value,char *mark, Types type)
{
    if(!isLegal(name))
        return 0;
    if(search(head,name))
        return 0;
    add(&head,name,value,mark,type);
    return 1;
}

int isLegal(char* symbol)
{
    int i;
    if(isalpha(symbol[0]) && strlen(symbol) <= MAX_SYMBOL_LEN)
    {
        for(int i=1;i<strlen(symbol);i++)
            if(!isalnum(symbol[i]))
                return 0;
        if(!isRegister(symbol) && !isInstuction(symbol) && !isDataType(symbol))
            return 1;
    }
    return 0;
}
