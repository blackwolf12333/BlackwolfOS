#include "linked_list.h"
#include "system.h"

void start_list(list_node *start, void *data) {
    start->index = 0;
    start->data = data;
    start->next = NULL;
}

void place_after(list_node *after, void *data) {
    
}

void add_to_list(list *l, void *data) {
	list_node new;
	new.index = l->end->index++;
	new.data = data;
	new.next = NULL;
	l->end->next = &new;
	l->end = &new;
}
