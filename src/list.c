#include "list.h"

list *createList(){
    list *flist = malloc(sizeof(list));
    flist->next = NULL;
    flist->name = NULL;
    flist->path = NULL;
    return flist;
}

list *addToList (char* name, char* path, int type, list *first) {

    while (first->next != NULL)
        first = first->next;
    first->next = malloc(sizeof(list));
    first = first->next;
    first->name = malloc(strlen(name)+1);
    strcpy(first->name, name);
    first->path = malloc(strlen(path)+1);
    strcpy(first->path, path);
    first->type = type;
    first->next = NULL;
    return first;
}

void deleteList(list *first) {
    if(first == NULL) return;
    while(first->next != NULL) {
        list *prev = first;
        first = first->next;
        free(prev->name);
        free(prev->path);
        free(prev);
    }
    free(first);
}

list* reverseList (list *first) {
    list* new_first = NULL;
    while(first) {
        list* next = first->next;
        first->next = new_first;
        new_first = first;
        first = next;
    }
    return new_first;
}

void showList (list *first)
{

    list *wsk = first;

    while(wsk!=NULL) {
        printf("%s %s\n", wsk->name, wsk->path);
        wsk = wsk->next;
    }
}

int listSize (list *first)
{

    list *wsk = first;

    int x=1;

    while (wsk->next!=NULL)
    {
        wsk = wsk->next;
        x++;
    }

    return x;
}

bool deleteItem (list *first, char* item)
{

  if(first == NULL)
    return false;

    list *wsk = first;
    list *temp;

    if(compare(first->path, item))
    {
      first = wsk->next;

      wsk->name = NULL;
      wsk->path = NULL;
      free(wsk);

      return true;
    }
    while(wsk != NULL) {
        if(compare(wsk->path, item)) {
            wsk->next = temp->next;
            temp->name = NULL;
            temp->path = NULL;
            free(temp);
            return true;
        }
        wsk = wsk->next;
    }
    return false;
}
