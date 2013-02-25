#include "linked_list.h"
#include "system.h"
#include "stdarg.h"

/*void start_list(list_node *start, void *data) {
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
}*/

void add_to_list(list *l, void *data) {
    list_node new;
    //printf("adding to list->processing \"%s\"->", data);
    if(l->start != NULL) {
    	//printf("adding\n");
   		new.index = l->end->index++;
   		new.data = (void*)kmalloc_a(sizeof(data));
    	new.data = data;
    	new.next = NULL;
    	l->end->next = &new;
    	l->end = &new;
    	l->current++;
    } else {
    	//printf("creating new starting point\n");
    	new.index = 0;
    	new.data = (void*)kmalloc_a(sizeof(data));
    	new.data = data;
    	new.next = NULL;
    	l->start = &new;
    	l->end = l->start;
    	l->current = 0;
    }
}
 
list *createlist(list *l, char *arg1, ...) {
    va_list args;
    va_start(args, arg1);
    char *arg = va_arg(args, char*);
    add_to_list(l, arg);
    while(arg != 0) {
		//printf("In creation loop->processing \"%s\"\n", arg);
        add_to_list(l, arg);
		arg = va_arg(args, char*);
    }
    return l;
}
 
void showlist(list l) {
    int i;
    list_node *node;
    //printf("list is at: %p\n", &l);
    //printf("first node of list is at: %p\n", l.start);
    node = l.start;
    //printf("Created starting node with data: %s\n", (char*)node->data);
    for(i = 0; i < l.current; i++) {
    	//printf("In the show loop");
        kprintf("%s ", (char*)node->data);
        node = node->next;
    }
}
