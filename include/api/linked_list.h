#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct list_node_t list_node;
 
struct list_node_t {
    int index;
    void *data;
    list_node *next;
};
 
typedef struct list {
    list_node *start;
    list_node *end;
    int current;
} list;

void add_to_list(list *l, void *data);
list *createlist(list *l, char *arg1, ...);
void showlist(list l); 

#endif
