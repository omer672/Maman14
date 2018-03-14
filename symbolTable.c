#include "symbolTable.h"

Symbol* head = NULL;

StatusCode isLegal(char* symbol)
{
    unsigned int i;
    if(isalpha(symbol[0]) && strlen(symbol) <= MAX_SYMBOL_LEN)
    {
        for(i=1;i<strlen(symbol);i++)
            if(!isalnum(symbol[i]))
                return illigal_symbol_name;
        if(!isRegister(symbol) && !isInstuction(symbol) && !isDataType(symbol))
            return success;
    }
    return illigal_symbol_name;
}

StatusCode setSymbol(char* name,int value,char *mark, Types type)
{
    if(isLegal(name) < 0)
        return illigal_symbol_name;
    if(search(head,name))
        return redeclaration_of_symbol;
    addSymbol(&head,name,value,mark,type);
    return success;
}

Symbol* getHead()
{
    return head;
}

Symbol* doesExist(char* name)
{
    return search(head,name);
}

