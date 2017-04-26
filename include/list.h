#ifndef LIST_H
#define LIST_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "cstring.h"
#include "bool.h"

typedef struct list list;

struct list {
  char* name;
  char* path;
  int type;
  list *next;
};

list *createList();
list *addToList (char *name, char *path, int type, list *first);
void showList (list *first);
int listSize(list *first);
bool deleteItem (list *first, char* item);
void deleteList (list *first);
list *reverseList (list *first);

#endif
