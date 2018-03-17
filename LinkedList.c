#include "LinkedList.h"

Symbol* alloc()
{
    return (Symbol*)malloc(sizeof(Symbol));
}

void addSymbol(Symbol** head,char* name,int value,SymbolType sType,int isEntry,Types type)
{
    Symbol* curr;
    if(*head == NULL)
    {
        *head = alloc();
        strcpy((*head)->name,name);
        (*head)->value = value;
        (*head)->symbolType = sType;
        (*head)->isEntry = isEntry;
        (*head)->type = type;
        (*head)->next = NULL;
    }
    else
    {
        curr = *head;
        while(curr->next)
            curr = curr->next;
        curr->next = alloc();
        strcpy(curr->next->name,name);
        curr->next->value = value;
        curr->next->symbolType = sType;
        curr->next->isEntry = isEntry;
        curr->next->type = type;
        curr->next->next = NULL;
    }
}

Symbol* search(Symbol* head, char* name)
{
    Symbol* curr = head;
    while(curr)
    {
        if(strcmp(curr->name,name) == 0)
            return curr;
        curr=curr->next;
    }
    return NULL;
}
