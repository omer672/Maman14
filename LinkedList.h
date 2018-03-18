#include "main.h"

/*The function gets new symbol node variables and adds it as a new node to linked list
 * Input: Symbol head, new symbol name, value, type, is a entry, is external/relocateable type
 * Output: NULL*/
void addSymbol(Symbol** head,char* name,int value,SymbolType sType,int isEntry, Types type);
/*The func gets a list head and symbol name and search if exists on list
 * Input: list head, symbol name
 * Output: if found, will return the node. else - NULL*/
Symbol *search(Symbol* head, char* name);
