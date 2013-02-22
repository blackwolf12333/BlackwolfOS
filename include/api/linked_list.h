#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct list_node_t list_node;
typedef struct list_t list;

typedef struct list_t {
	list_node *start;
	list_node *end;
	int current;
} list;

typedef struct list_node_t {
	int index;
    void *data;
    list_node *next;
} list_node;

void start_list(list_node *start, void *data);

#endif
