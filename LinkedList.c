#include "LinkedList.h"

Symbol* alloc()
{
    return (Symbol*)malloc(sizeof(Symbol));
}

void add(Symbol** head,char* name,int value,char* mark,Types type)
{
    Symbol* curr;
    if(*head == NULL)
    {
        *head = alloc();
        (*head)->name = name;
        (*head)->value = value;
        (*head)->mark = mark;
        (*head)->type = type;
        (*head)->next = NULL;
    }
    else
    {
        curr = *head;
        while(curr->next)
            curr = curr->next;
        curr->next = alloc();
        curr->next->name = name;
        curr->next->value = value;
        curr->next->mark = mark;
        curr->next->type = type;
        curr->next->next = NULL;
    }
}

int search(Symbol* head, char* name)
{
    Symbol* curr = head;
    while(curr)
    {
        if(strcmp(curr->name,name))
            return 1;
    }
    return 0;
}
