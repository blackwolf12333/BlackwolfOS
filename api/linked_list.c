#include "linked_list.h"
#include "system.h"

list_node *start_list(list_node *start, void *data) {
    start->data = data;
    start->next = NULL;
    return start;
}

void place_after(list_node *after, void *data) {
    
}
