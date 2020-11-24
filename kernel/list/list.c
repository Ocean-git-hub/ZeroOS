#include <zero/list.h>

void list_initialize(ListStruct *list) {
    list->next = list;
    list->prev = list;
}

void list_insert_node(ListStruct *node, ListStruct *prev_node, ListStruct *next_node) {
    node->prev = prev_node;
    node->next = next_node;
    prev_node->next = node;
    next_node->prev = node;
}

void list_add_node(ListStruct *list, ListStruct *new_node) {
    list_insert_node(new_node, list, list->next);
}

void list_add_node_tail(ListStruct *list, ListStruct *new_node) {
    list_insert_node(new_node, list->prev, list);
}

void list_delete_node(ListStruct *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    list_initialize(node);
}

void list_replace_node(ListStruct *old_node, ListStruct *new_node) {
    new_node->prev = old_node->prev;
    new_node->next = old_node->prev;
    new_node->prev->next = new_node;
    new_node->next->prev = new_node;
}

void list_move_node(ListStruct *move_node, ListStruct *dest_list) {
    list_delete_node(move_node);
    list_add_node(move_node, dest_list);
}

void list_move_node_tail(ListStruct *move_node, ListStruct *dest_list) {
    list_delete_node(move_node);
    list_add_node_tail(move_node, dest_list);
}

bool list_is_empty(ListStruct *list) {
    return list->next == list;
}

void list_insert_list(ListStruct *list, ListStruct *prev_node, ListStruct *next_node) {
    if (!list_is_empty(list)) {
        list->next->prev = prev_node;
        list->prev->next = next_node;
        prev_node->next = list->next;
        next_node->prev = list->prev;
    }
}

void list_splice_list(ListStruct *src_list, ListStruct *dest_list) {
    list_insert_list(src_list, dest_list, dest_list->next);
    list_initialize(src_list);
}

void list_splice_list_tail(ListStruct *src_list, ListStruct *dest_list) {
    list_insert_list(src_list, dest_list->prev, dest_list);
    list_initialize(src_list);
}
