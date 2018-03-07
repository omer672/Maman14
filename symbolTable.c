#include "symbolTable.h"

Symbol* head = NULL;

int isLegal(char* symbol)
{
    unsigned int i;
    if(isalpha(symbol[0]) && strlen(symbol) <= MAX_SYMBOL_LEN)
    {
        for(i=1;i<strlen(symbol);i++)
            if(!isalnum(symbol[i]))
                return 0;
        if(!isRegister(symbol) && !isInstuction(symbol) && !isDataType(symbol))
            return 1;
    }
    return 0;
}

int setSymbol(char* name,int value,char *mark, Types type)
{
    if(!isLegal(name))
        return 0;
    if(search(head,name))
        return 0;
    add(&head,name,value,mark,type);
    return 1;
}

Symbol* getHead()
{
    return head;
}

Symbol* doesExist(char* name)
{
    return search(head,name);
}

