#define FIFO 1
#define LRU 2

typedef struct node *address_node;

address_node create_node();
int search_node(address_node start, int value, int mode);
void append_node(address_node start, int value);
void remove_first(address_node start);
void print_all(address_node start);
void destroy(address_node start);
void clear(address_node start);