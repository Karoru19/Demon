#include "list.h"
#include "cstring.h"
#include "bool.h"
#include <stdio.h>
#include <stdlib.h>

void addToList (string nameData, string pathData, list *first) {
    list *newNode = (list*)malloc(sizeof(list));

    if(newNode == NULL){
        fprintf(stderr, "Unable to allocate memory for new node\n");
        exit(-1);
    }

    newNode->name = nameData;
    newNode->path = pathData;
    newNode->next = NULL;

    if(first->name == NULL){
        first->name = newNode->name;
        first->path = newNode->path;
	first->next = newNode->next;
    }
    else if(first->next == NULL){
        first->next = newNode;
    }
    else {
        list *current = first;
        while (true) {
            if(current->next == NULL) {
                current->next = newNode;
                break;
            }
            current = current->next;
        };
    }
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

bool deleteItem (list *first, string item)
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

    temp = wsk;
    wsk = wsk->next;

    while(wsk != NULL)
    {
      if(compare(wsk->path, item))
      {
        temp->next = wsk->next;
        wsk->name = NULL;
        wsk->path = NULL;
        free(wsk);
        return true;
      }
      temp = wsk;
      wsk = wsk->next;
    }

    return false;
}

void deleteList(list *head) {
    while (head) {
        list *tmp = head->next;
        free(head);
        head = tmp;
        }
}

list* reverseList (list *pierwszy) {
    list* new_first = NULL;
    while(pierwszy) {
        list* next = pierwszy->next;
        pierwszy->next = new_first;
        new_first = pierwszy;
        pierwszy = next;
    }
    return new_first;
}
