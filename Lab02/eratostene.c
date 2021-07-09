#include <stdio.h>

typedef int T;
#include "SortedList.h"

TSortedList getNaturals(int A, int B) {
    TSortedList nats = NULL;
    int i;
    for (i = A; i <= B; i++) {
        nats = insert(nats, i);
    }
    return nats;
}

TSortedList getPrimes(int N) {
    TSortedList nats = getNaturals(2, N);

    // TODO: Cerința Bonus

    TSortedList head = nats;
    TSortedList stage = nats;

    while (!isEmpty(stage))
    {
        int value = stage->value;
        nats = stage;
        while (!isEmpty(nats->next))
        {
            if(nats->next->value % value == 0)
            {
                TSortedList toBeDeleted = nats->next;
                if (!isEmpty(nats->next->next))
                {
                    nats->next = nats->next->next;
                }
                else
                {
                    nats->next == NULL;
                    break;
                }
                
               free(toBeDeleted);
            }
            nats = nats->next;
        }
        stage = stage->next;
        
    }
    nats = head;

    return nats;
}

void printInts(TSortedList list) {
    while (!isEmpty(list)) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    printInts(getPrimes(100));
    return 0;
}
