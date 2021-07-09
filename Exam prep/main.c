#include <stdio.h>
#include <string.h>
typedef int T;
typedef int Item;

#include "SortedList.h"
#include "tree.h"

int main () {
    int value = 10;
    TSortedList list = create(value);
    value = 2;
    list = insert(list,value); 
    printf("%d %d\n", list->value, list->next->value);
    
    return 0;
}