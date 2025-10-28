#include "linked-list.h"
#include <string.h>

// Create empty linked list function
linkedList_h* create_linked_list(void) {

    linkedList_h* L;
    
    // L = (linkedList_h*)malloc(sizeof(linkedList_h));
    // malloc() return void* type pointer
    // So type casting is useless
    // void* is automatically converted to any type pointer
    L = malloc(sizeof(linkedList_h));
    L->head = NULL; // empty list, so NULL
    
    return L;
}

// Free all linked list memory function
void free_linked_list(linkedList_h* L){
    listNode* p;
    while (L->head !=NULL) {
        p = L->head;
        L->head = L->head->link;
        free(p);
        p = NULL;
    }
}
/**********************************************************
┌─────────────┐
│ linkedList_h│  
│  head: 0x200│──┐  (0x100 -> 0x200)
└─────────────┘  │
                 │
    ┌────────────┘
    ▼
┌─────────────┐     ┌─────────────┐     ┌─────────────┐
│  listNode   │     │  listNode   │     │  listNode   │
│  data: ...  │     │  data: ...  │     │  data: ...  │
│  link: 0x200│     │  link: 0x300│────>│  link: NULL │
└─────────────┘     └─────────────┘     └─────────────┘
 0x100               0x200               0x300
 ▲                   ▲
 │                   │
 p                   L->head


> If all memory is free

┌─────────────┐
│ linkedList_h│  
│  head: 0x200│──┐
└─────────────┘  │
                 │
    ┌────────────┘
    ▼
╔═════════════╗     ┌─────────────┐     ┌─────────────┐
║  free!      ║     │  listNode   │     │  listNode   │
║  (trash)    ║     │  data: ...  │     │  data: ...  │
║             ║     │  link: 0x300│────>│  link: NULL │
╚═════════════╝     └─────────────┘     └─────────────┘
 0x100 (Can't use)  0x200               0x300
 ▲                   ▲
 │                   │
 p                   L->head

 ***********************************************************/

 void print_list(linkedList_h* L){
    listNode* p;
    printf("L = (");
    p = L->head;
    while (p!=NULL){
        printf("%s", p->data);
        p = p->link;
        
        if (p !=NULL){
            printf(", ");
        }
    }
    printf(") \n");
}

void insert_first_node(linkedList_h *L, char *x)
{
    listNode* new_node;
    //allocate new node
    // new_node = (listNode*)malloc(sizeof(listNode)); in c++, type casting is needed, also for explicitness
    new_node = malloc(sizeof(listNode));
    //sizeof(listNode)
    // structure size is calcuate base by architecture. for example, ARMv8 is 16 bytes.
    // char data : 4bytes, + padding bit : 4bytes | struct listNode* link = 8bytes
    strcpy(new_node->data, x); //store data (x) in new node
/*
* Example : 
*   char src[] = "hello";
*    char dest[10];
*    strcpy(dest, src);
***************************************************************
* Before execute strcpy:
*    src:  ['h']['e']['l']['l']['o']['\0']
*           ↑
*           src pointer
*
*    dest: [???][???][???][???][???][???][???][???][???][???]
*           ↑
*           dest pointer
****************************************************************
* After execute strcpy:
*   src:  ['h']['e']['l']['l']['o']['\0']
*
*   dest: ['h']['e']['l']['l']['o']['\0'][???][???][???][???]
*/
    new_node->link = L->head;
    L->head = new_node;
}

// Insert new node after pre
void insert_middle_node(linkedList_h* L, listNode *pre, char* x)
{
    listNode* new_node;
    //new_node = (listNode*)malloc(sizeof(listNode));
    new_node = malloc(sizeof(listNode));
    strcpy(new_node->data, x);

    if (L->head == NULL) { // if list is empty
        new_node->link = NULL; // link new node to first and last node
        L->head = new_node;
    }
    else if (pre == NULL) { // if pre(pointer that decide location to insert new node) is NULL)
        new_node->link = L->head; // insert new node into first position
        L->head = new_node; 
    }
    else {
        new_node->link = pre->link; // link new node after pointer pre
        pre->link = new_node;
    }
}

void insert_last_node(linkedList_h* L, char* x)
{
    listNode* new_node;
    listNode* temp;
    
    //new_node = (listNode*)malloc(sizeof(listNode));
    new_node = malloc(sizeof(listNode));
    strcpy(new_node->data, x);

    new_node->link = NULL;
    
    if (L->head == NULL){ // if list is empty
        L->head = new_node; // link new node to first node of list
        return;
    }
    // if list is not empty
    temp = L->head;
    while (temp->link !=NULL) { // find last node of list
        temp = temp->link; // link new node next of last node(temp)
    }
    temp->link = new_node;

}

void delete_node(linkedList_h* L, listNode* p)
{
    listNode* pre; // Pointer of previous node that going to delete

    if (L->head == NULL) { // If list if empty, return
        return;
    }

    if (L->head->link == NULL) { // If list has only one node,
        free(L->head); // Free the first node
        L->head = NULL; // And list start pointer -> to NULL
        return;
    }
    else if (p == NULL) { // If there is no node to delete, return
        return;
    }
    else { // Find previous node of p to be deleted, using the pointer pre
        pre = L->head;

        while (pre->link != p) {
            pre = pre->link;
        }

        pre->link = p->link; // Link previous node of p to be deleted, to next node
        free(p); // Free delete node
    }
}
/**********************************************************
Delete middle node: L = (Monday, Wednesday, Friday) → (Monday, Friday)

Before:
       ┌─────┐      ┌───────────┐      ┌────────┐
       │  M  │ ───▶ │     W     │ ───▶ │   F    │ ───▶ NULL
       └─────┘      └───────────┘      └────────┘
        ▲            ▲
        pre          p (delete this)

After pre->link = p->link:
       ┌─────┐                         ┌────────┐
       │  M  │ ─────────────────────▶  │   F    │ ───▶ NULL
       └─────┘       ╳                 └────────┘
                ┌───────────┐
                │     W     │ (isolated)
                └───────────┘
                 ▲
                 p

After free(p):
       ┌─────┐                         ┌────────┐
       │  M  │ ─────────────────────▶  │   F    │ ───▶ NULL
       └─────┘                         └────────┘
                ╔═══════════╗
                ║   freed   ║
                ╚═══════════╝
**********************************************************/ // Find x node in the list
listNode* search_node(linkedList_h* L, char* x)
{
    listNode* temp;
    temp = L->head;

    while (temp !=NULL) {
        if (strcmp(temp->data, x) == 0) {
            return temp;
        }
        else {
            temp = temp->link;
        }
    }
}
/**********************************************************
Search "Wednesday" in L = (Monday, Wednesday, Friday)

Step 1:     Step 2:     Step 3 (Found!):
┌─────┐    ┌─────┐     ┌─────┐
│  M  │───▶│  W  │────▶│  F  │───▶ NULL
└─────┘    └─────┘     └─────┘
 ▲          ▲
temp      temp (return this)
"M"!="W"  "W"=="W" ✓
**********************************************************/

// Reverse node order in linked list
void reverse(linkedList_h* L)
{
    listNode* p;
    listNode* q;
    listNode* r;

    p = L->head; // Set pointer p into first node
    q = NULL;
    r = NULL;

    // Start first node, follow the link to next node and change the link
    while (p != NULL) {
        r = q;
        q = p;
        p = p->link;
        q->link = r;
    }
    L->head = q;
}
/**********************************************************
Reverse: L = (M, W, F) → (F, W, M)
Three pointers: r(prev), q(current), p(next)

Initial:           Iter 1:           Iter 2:           Iter 3:
┌─┐  ┌─┐  ┌─┐    ┌─┐  ┌─┐  ┌─┐    ┌─┐  ┌─┐  ┌─┐    ┌─┐  ┌─┐  ┌─┐
│M│─▶│W│─▶│F│──▶ │M│  │W│─▶│F│──▶ │M│◀─│W│  │F│──▶ │M│◀─│W│◀─│F│
└─┘  └─┘  └─┘    └─┘  └─┘  └─┘    └─┘  └─┘  └─┘    └─┘  └─┘  └─┘
 ▲               NULL  ▲    ▲           ▲    ▲    ▲           ▲    ▲
 p                     q    p           r    q    p           r    q
q=NULL                r=q              r=q                   r=q   p=NULL
r=NULL                q=p              q=p                   q=p
                      p=p->link        p=p->link             p=p->link
                      q->link=r        q->link=r             q->link=r

Final: L->head = q
       ┌─┐  ┌─┐  ┌─┐
  NULL◀─│M│◀─│W│◀─│F│
       └─┘  └─┘  └─┘
                  ▲
                L->head
**********************************************************/
