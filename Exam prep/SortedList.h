#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <stdlib.h>
#include <assert.h>

/*
    IMPORTANT!

    As we stick to pure C, we cannot use templates. We will just asume
    some type T was previously defined.
*/

// -----------------------------------------------------------------------------

typedef struct node {
    T value;
    struct node* next;
} TNode, *TSortedList;

// TODO : Cerința 1 & Cerința 2

TSortedList create(T value) {

    TSortedList list = (TSortedList) calloc(1,sizeof(TNode));
    list->value = value;
    list->next = NULL;

    return list;
}

int isEmpty(TSortedList list) {

    if (list == NULL)
    {
        return 1;
    }
    else 
    {
        return 0;
    }
    

    return 0;
}

TSortedList insert(TSortedList list, int value) {

    TSortedList head = list;
    int ok = 1;

    if (list == NULL)
    {
        list = create(value);
        return list;
    }

    while (list->next != NULL)
    {
        list = list->next;
    }
    
    list->next = (TSortedList) calloc(1,sizeof(TNode));
    list = list->next;
    list->value = value;
    list->next = NULL;
    list = head;

    return head;
}

int contains(TSortedList list, int value) {

    TSortedList cl = list;
    while (cl != NULL)
    {
        if(cl->value == value) 
        {
            return 1;
        }
        cl = cl->next;
    }
    
    return 0;
}

TSortedList deleteOnce(TSortedList list, int value) {

    TSortedList head = list;
    if (list->value == value)
    {
        list = list->next;
        free(head);
        return list;
    }    
    TSortedList last;
    while (list->next != NULL)
    {
        last = list;
        list = list->next;
    }
    if (list->value == value)
    {
        free(list);
        last->next = NULL;
        return head;
    }

    list = head;
    
    while (list->next != NULL && list->next->value != value)
    {
        list = list->next;
    }
    TSortedList aux;
    aux = list->next;
    list->next = aux->next;
    free(aux);
    
    return head;
}

int length (TSortedList list) {
    
    int l = 0;
    TSortedList head = list;
    while (list != NULL)
    {
        l++;
        list = list->next;
    }
    return l;
}

T getNth (TSortedList list, int n) {
    
    TSortedList head = list;
    for (int i = 1; i < n; i++)
    {
        head = head->next;
    }

    return head->value;
}

TSortedList freeTSortedList (TSortedList list) {
    TSortedList next = list;

    while (next != NULL)
    {   list = next;
        next = list->next;
        free(list);
    }

    return list;
    
}

#endif
