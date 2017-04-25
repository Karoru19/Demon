#include "list.h"
#include "cstring.h"
#include "bool.h"
#include <stdio.h>
#include <stdlib.h>

void addToList (string nameData, string pathData, el_listy *head) {
    el_listy *newNode = (el_listy*)malloc(sizeof(el_listy));

    if(newNode == NULL){
        fprintf(stderr, "Unable to allocate memory for new node\n");
        exit(-1);
    }

    newNode->name = nameData;
    newNode->path = pathData;
    newNode->next = NULL;

    if(head->name == NULL){
        head->name = newNode->name;
        head->path = newNode->path;
    }
    else if(head->next == NULL){
        head->next = newNode;
    }
    else {
        el_listy *current = head;
        while (true) {
            if(current->next == NULL) {
                current->next = newNode;
                break;
            }
            current = current->next;
        };
    }
}

void showList (el_listy *pierwszy) {
    el_listy *wsk = pierwszy;

    while(wsk!=NULL) {
        printf("%s %s\n", wsk->name, wsk->path);
        wsk = wsk->next;
    }
}

void deleteList(el_listy *head) {
    while (head) {
        el_listy *tmp = head->next;
        free(head);
        head = tmp;
        }
}

el_listy* reverseList (el_listy *pierwszy) {
    el_listy* new_first = NULL;
    while(pierwszy) {
        el_listy* next = pierwszy->next;
        pierwszy->next = new_first;
        new_first = pierwszy;
        pierwszy = next;
    }
    return new_first;
}
