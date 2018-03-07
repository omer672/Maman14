#include "commandsToBinary.h"

void markEntry(char* symbol)
{
    Symbol* sym;
    int i = 0;
    char name[strlen(symbol)];
    char* token;
    char delimiter[11] = " \t\n\v\f\r"; /* all of the whitespace chars*/
    token = strtok(symbol,delimiter);

    while(token != NULL)
    {
        if(i==1)
            strcpy(name,token);
        i++;
        token = strtok(NULL,delimiter);
    }
    if(i!=1)
    {
        if(i==0)
            /*ERROR : no openrands*/;
        if(i>1)
            /*ERROR : i opernands found,expected 1*/;
    }
    else
    {
        if((sym = doesExist(name)) != NULL)
        {
            sym->mark = ENTRY;
        }
        else
        {
            /* ERROR: symbol doesnt exist */
        }
    }
}
