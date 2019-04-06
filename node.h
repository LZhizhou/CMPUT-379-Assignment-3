#include <stdio.h>
 #include <stdlib.h>


#define FIFO 1
#define LRU 2

typedef struct node *address_node;

address_node create_node();

int search_node(address_node temp, int value, int mode);
void append_node(address_node temp, int value);
address_node remove_first(address_node temp, int value);