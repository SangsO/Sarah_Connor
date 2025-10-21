#include <stdio.h>
#include <stdlib.h>


typedef struct listNode {
    char data[10];
    struct ListNode* link;
}listNode;

typedef struct {
    listNode* head;
} linkedList_h;

linkedList_h* create_linked_list(void);
void free_linked_list(linkedList_h* L);
void print_list(linkedList_h* L);
void insert_first_node(linkedList_h *L, char *x);
void insert_middle_node(linkedList_h* L, listNode *pre, char* x);
void insert_last_node(linkedList_h* L, char* x);