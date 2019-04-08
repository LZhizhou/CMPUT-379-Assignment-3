#include <stdio.h>
#include <stdlib.h>
#include <malloc/malloc.h>
#include "node.h"

struct node
{
    unsigned int address;
    struct node *next;
};

address_node create_node()
{
    address_node start;
    start = malloc(sizeof(start));
    start->address = 0;
    start->next = NULL;
    return start;
}

int search_node(address_node start, int value, int mode)
{
    address_node previous = start;
    address_node current = start->next;
    if (current==NULL) {
        return 0;
    }
    
    address_node next = current->next;
    while (current->address != value)
    {
        if (next == NULL)
        {
            return 0;
        }
        previous = current;
        current = next;
        next = current->next;
    }
    switch (mode)
    {
    case LRU:
        if (next==NULL){
            return 1 ;
        }
        //printf("%d: ", value);
        //print_all(start);

        previous->next = next;

        address_node temp = current;
        while (next != NULL)
        {
            previous = current;
            current = next;
            next = current->next;
        }
        temp->next = NULL;
        current->next = temp;
        //printf("after: ");
        //print_all(start);

    case FIFO:
        return 1;
    }
    return 1;
}
void append_node(address_node start, int value)
{
    address_node i = start;
    while (i->next != NULL)
    {
        i = i->next;
    }
    address_node last;
    last = malloc(sizeof(last));
    last->address = value;
    last->next = NULL;
    i->next = last;
}
void remove_first(address_node start)
{
    address_node current = start->next;
    address_node next = current->next;
    start->next = next;
    free(current);
}

void print_all(address_node start)
{
    address_node i = start;
    while (i != NULL)
    {
        printf("value: %d,\n", i->address);
        i = i->next;
    }
    printf("end print\n");
}
void clear(address_node start){


    destroy(start->next);
    start->next = NULL;
    
}
void destroy(address_node start){


    if (start->next!=NULL) {
        destroy(start->next);
    }
    free(start);
    
}
