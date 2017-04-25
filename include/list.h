#ifndef LIST_H
#define LIST_H

#include "cstring.h"
#include "bool.h"

typedef struct lista
{
    string name;
	string path;
    struct lista *next;
}el_listy;

void addToList (string name, string path, el_listy *pierwszy);
void showList (el_listy *pierwszy);
void deleteList (el_listy *head);
el_listy* reverseList (el_listy *pierwszy);

#endif
