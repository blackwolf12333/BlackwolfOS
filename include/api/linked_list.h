#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct list_node_t {
    void *data;
    struct list_node_t *next;
} list_node;

list_node *start_list(list_node *start, void *data);

#endif
