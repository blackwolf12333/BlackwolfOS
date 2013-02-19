#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct node_t {
    void *data;
    struct node_t *next;
} node;

node *start_list(void *data);

#endif
