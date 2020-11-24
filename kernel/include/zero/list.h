#ifndef ZEROOS_LIST_H
#define ZEROOS_LIST_H

#include <stdbool.h>
#include <zero/kernel.h>

#define list_get_entry(list_pointer, node_struct, list_member_name) \
    structure_container_of(list_pointer, node_struct, list_member_name)

#define list_get_first_entry(list_pointer, node_struct, list_member_name) \
    structure_container_of((list_pointer)->next, node_struct, list_member_name)

typedef struct ListStruct ListStruct;

struct ListStruct {
    ListStruct *next;
    ListStruct *prev;
};

void list_initialize(ListStruct *list);

void list_insert_node(ListStruct *node, ListStruct *prev_node, ListStruct *next_node);

void list_add_node(ListStruct *list, ListStruct *new_node);

void list_add_node_tail(ListStruct *list, ListStruct *new_node);

void list_delete_node(ListStruct *node);

void list_replace_node(ListStruct *old_node, ListStruct *new_node);

void list_move_node(ListStruct *move_node, ListStruct *dest_list);

void list_move_node_tail(ListStruct *move_node, ListStruct *dest_list);

bool list_is_empty(ListStruct *list);

void list_insert_list(ListStruct *list, ListStruct *prev_node, ListStruct *next_node);

#endif //ZEROOS_LIST_H
