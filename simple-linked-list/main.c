#include <stdio.h>
#include "linked-list.h"

int main (void) 
{
    linkedList_h *L;
    L = create_linked_list();
    printf("(1) Create empty list\n");
    print_list(L);

    printf("(2) Insert [Wednesday] node is list\n");
    insert_first_node(L, "Wednesday");
    print_list(L);

    printf("(3) Insert [Friday] node at last of list\n");
    insert_last_node(L, "Friday");
    print_list(L);

    printf("(4) Insert [Monday] node at first of list\n");
    insert_first_node(L, "Monday");
    print_list(L);

    printf("(5) Free list space and make list empty list\n");
    free_linked_list(L);
    print_list(L);

    getchar();
    return 0;
}
/*
1) Create empty list
   Call: L = create_linked_list();
   Effect: allocate one linkedList_h in heap, set head = NULL.

Stack                              Heap
┌──────────────┐                  ┌─────────────┐
│ L (pointer) ─┼───────▶          │ linkedList_h│
└──────────────┘                  │  head: NULL │
                                  └─────────────┘
Print: L = ()

──────────────────────────────────────────────────────────────────────────────
2) Insert [Wednesday] node at first
   Call: insert_first_node(L, "Wednesday");
   Steps:
     - Allocate node N1.
     - Copy "Wednesday" into N1->data.
     - N1->link = L->head (NULL).
     - L->head = N1.

Stack                              Heap
┌──────────────┐                  ┌─────────────┐
│ L (pointer) ─┼───────▶          │ linkedList_h│
└──────────────┘                  │  head: ─────┼───────────┐
                                  └─────────────┘           │
                                                            ▼
                                                      ┌─────────────┐
                                                      │ listNode N1 │ (0x100)
                                                      │ "Wednesday" │
                                                      │ link: NULL  │
                                                      └─────────────┘
Print: L = (Wednesday)

──────────────────────────────────────────────────────────────────────────────
3) Insert [Friday] node at last
   Call: insert_last_node(L, "Friday");
   Steps:
     - Allocate node N2; N2->data="Friday"; N2->link=NULL.
     - Walk from L->head (N1) to last node (N1).
     - Set last->link = N2.

Stack                              Heap
┌──────────────┐                  ┌─────────────┐
│ L (pointer) ─┼───────▶          │ linkedList_h│
└──────────────┘                  │  head: ─────┼───────────┐
                                  └─────────────┘           │
                                                            ▼
                                                      ┌─────────────┐      ┌─────────────┐
                                                      │ listNode N1 │ ───▶ │ listNode N2 │
                                                      │ "Wednesday" │      │  "Friday"   │
                                                      │ link:0x200  │      │ link: NULL  │
                                                      └─────────────┘      └─────────────┘
Print: L = (Wednesday, Friday)

──────────────────────────────────────────────────────────────────────────────
4) Insert [Monday] node at first
   Call: insert_first_node(L, "Monday");
   Steps:
     - Allocate node N0; N0->data="Monday".
     - N0->link = L->head (N1).
     - L->head = N0.

Stack                              Heap
┌──────────────┐                  ┌─────────────┐
│ L (pointer) ─┼───────▶          │ linkedList_h│
└──────────────┘                  │  head: ─────┼───────────────────────┐
                                  └─────────────┘                       │
                                                                        ▼
                                                                 ┌─────────────┐      ┌─────────────┐      ┌─────────────┐
                                                                 │ listNode N0 │ ───▶ │ listNode N1 │ ───▶ │ listNode N2 │
                                                                 │  "Monday"   │      │ "Wednesday" │      │  "Friday"   │
                                                                 │ link:0x100  │      │ link:0x200  │      │ link: NULL  │
                                                                 └─────────────┘      └─────────────┘      └─────────────┘
Print: L = (Monday, Wednesday, Friday)

──────────────────────────────────────────────────────────────────────────────
5) Free the entire list (head-first iteration)
   Call: free_linked_list(L);

Loop iteration #1:
  p = L->head (N0)
  L->head = N0->link (N1)
  free(N0)

┌─────────────┐
│ linkedList_h│  
│  head: N1   │──┐  (N0 → N1)
└─────────────┘  │
                 ▼
╔═════════════╗     ┌─────────────┐      ┌─────────────┐
║   free N0   ║     │ listNode N1 │ ───▶ │ listNode N2 │
╚═════════════╝     │ "Wednesday" │      │  "Friday"   │
                    │ link:0x200  │      │ link: NULL  │
                    └─────────────┘      └─────────────┘

Loop iteration #2:
  p = L->head (N1)
  L->head = N1->link (N2)
  free(N1)

┌─────────────┐
│ linkedList_h│  
│  head: N2   │──┐  (N1 → N2)
└─────────────┘  │
                 ▼
╔═════════════╗     ╔═════════════╗     ┌─────────────┐
║   free N0   ║     ║   free N1   ║     │ listNode N2 │
╚═════════════╝     ╚═════════════╝     │  "Friday"   │
                                        │ link: NULL  │
                                        └─────────────┘

Loop iteration #3:
  p = L->head (N2)
  L->head = N2->link (NULL)
  free(N2)

┌─────────────┐
│ linkedList_h│  
│  head: NULL │   (list is empty)
└─────────────┘

╔═════════════╗  ╔═════════════╗  ╔═════════════╗
║   free N0   ║  ║   free N1   ║  ║   free N2   ║
╚═════════════╝  ╚═════════════╝  ╚═════════════╝

Print: L = ()
*/