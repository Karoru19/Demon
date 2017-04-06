#include "list.h"
#include "cstring.h"
#include "bool.h"
#include <stdio.h>
#include <stdlib.h>

void addToList (string nameData, string pathData, el_listy *pierwszy)
{
    el_listy *wsk, *nowy;

    wsk = pierwszy;

    while (wsk->next !=NULL)
    {
        wsk = wsk->next;
    }

    nowy = malloc(sizeof(el_listy));
    nowy->name = nameData;
 	nowy->path = pathData;
    nowy->next = NULL;
    wsk->next = nowy;

}

void showList (el_listy *pierwszy)
{

    el_listy *wsk = pierwszy;

    while(wsk!=NULL)
    {
        printf("%s %s\n", wsk->name, wsk->path);
        wsk = wsk->next;
    }
}
