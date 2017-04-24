#include "list.h"
#include "cstring.h"
#include "bool.h"
#include <stdio.h>
#include <stdlib.h>

void addToList (string nameData, string pathData, list *first)
{
    list *wsk, *new;

    wsk = first;

    while (wsk->next !=NULL)
    {
        wsk = wsk->next;
    }

    new = malloc(sizeof(list));
    new->name = nameData;
 	  new->path = pathData;
    new->next = NULL;
    wsk->next = new;

}

void showList (list *first)
{

    list *wsk = first;

    while(wsk!=NULL)
    {
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

bool deleteItem (list *first, string item)
{

  if(first == NULL)
    return false;

    list *wsk = first;
    list *temp;

    if(compare(wsk->path, item))
    {
      first = wsk->next;
      wsk->name = NULL;
      wsk->path = NULL;
      free(wsk);
      return true;
    }

    while(wsk != NULL)
    {
      if(compare(wsk->path, item))
      {
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
