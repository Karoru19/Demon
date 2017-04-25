#ifndef LIST_H
#define LIST_H

#include "cstring.h"
#include "bool.h"

typedef struct lista
{
  string name;
  string path;
  struct lista *next;
}list;

void addToList (string name, string path, list *first);
void showList (list *first);
int listSize(list *first);
bool deleteItem (list *first, string item);
void deleteList (list *first);
list* reverseList (list *first);

#endif
