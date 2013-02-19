#include "linked_list.h"

node *start_list(void *data) {
    node n;
    n.data = data;
    n.next = NULL;
    return &n;
}
