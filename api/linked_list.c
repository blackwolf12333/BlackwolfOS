#include "linked_list.h"
#include "stdio.h"

node *start_list(void *data) {
    node n;
    n.data = data;
    n.next = NULL;
    return &n;
}

void place_after(node *after, void *data) {
    node *next;
    node new;
    new.data = data;
    new.next = after->next;
    while((next = new->next) != NULL) {
        next->next = next;
    }
}
