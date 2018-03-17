#include "LinkedList.h"
/*The function allocates new memory for symbols*/
Symbol* alloc()
{
    return (Symbol*)malloc(sizeof(Symbol));
}
/*The function gets new symbol node variables and adds it as a new node to linked list
 * Input: Symbol head, new symbol name, value, type, is a entry, is external/relocateable type
 * Output: NULL*/
void addSymbol(Symbol** head,char* name,int value,SymbolType sType,int isEntry,Types type)
{
    Symbol* curr;
    if(*head == NULL)/*checks if head doesn't exists*/
    {
        *head = alloc();
        strcpy((*head)->name,name);
        (*head)->value = value;
        (*head)->symbolType = sType;
        (*head)->isEntry = isEntry;
        (*head)->type = type;
        (*head)->next = NULL;
    }
    else/*if head exist*/
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
/*The func gets a list head and symbol name and search if exists on list
 * Input: list head, symbol name
 * Output: if found, will return the node. else - NULL*/
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
