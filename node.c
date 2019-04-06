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
    address_node previous = NULL;
    address_node current = start;
    address_node next = start->next;
    while (current->address != value)
    {
        previous = current;
        current = start;
        next = current->next;
        if (next == NULL)
        {
            return 0;
        }
    }
    switch (mode)
    {
    case LRU:
        if (previous == NULL)
        {
            start->address = next->address;
            start->next = next->next;
            free(next);
            append_node(start, value);
        }
        else
        {
            previous->next = next;
            free(current);
            append_node(next, value);
        }
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
address_node remove_first(address_node start, int value)
{
    append_node(start, value);
    address_node res = start->next;
    free(start);
    return res;
}