#include <stdio.h>
#include <stdlib.h>
#include "linked-list.h"

int main(void) {
    linkedList_h *L;
    listNode *p;
    L = create_linked_list(); // create empty list
    
    printf("(1) insert [[Monday], [Wednesday], [Sunday] into list\n");
    insert_last_node(L, "Monday");
    insert_last_node(L, "Wednesday");
    insert_last_node(L, "Sunday");
    print_list(L);

    printf("\n(2) Search [Wednesday] node in list\n");
    p = search_node(L, "Wednesday");
    if (p == NULL) {
        printf("No data that you want to search\n");
    }
    else {
        printf("[%s] found !\n", p->data);
    }

    printf("\n(3) Insert [Friday] node after [Wednesday] node\n");
    insert_middle_node(L, p, "Friday");
    print_list(L);

    printf("\n(4) Delete [Sunday] node in list\n");
    p = search_node(L, "Sunday");
    delete_node(L, p);
    print_list(L);

    printf("\n(5) Reverse the list\n");
    reverse(L);
    print_list(L);

    free_linked_list(L);
    getchar();

    return 0;
}
/*
──────────────────────────────────────────────────────────────────────────────
1) Insert three nodes at end: Monday, Wednesday, Sunday
   Call: insert_last_node(L, "Monday");
         insert_last_node(L, "Wednesday");
         insert_last_node(L, "Sunday");

After first insert (Monday):
┌─────────────┐
│ linkedList_h│  
│  head: ─────┼───────┐
└─────────────┘       │
                      ▼
                ┌─────────────┐
                │ listNode N1 │ (0x100)
                │  "Monday"   │
                │ link: NULL  │
                └─────────────┘

After second insert (Wednesday):
┌─────────────┐
│ linkedList_h│  
│  head: ─────┼───────┐
└─────────────┘       │
                      ▼
                ┌─────────────┐      ┌─────────────┐
                │ listNode N1 │ ───▶ │ listNode N2 │ (0x200)
                │  "Monday"   │      │ "Wednesday" │
                │ link:0x200  │      │ link: NULL  │
                └─────────────┘      └─────────────┘

After third insert (Sunday):
┌─────────────┐
│ linkedList_h│  
│  head: ─────┼───────┐
└─────────────┘       │
                      ▼
                ┌─────────────┐      ┌─────────────┐      ┌─────────────┐
                │ listNode N1 │ ───▶ │ listNode N2 │ ───▶ │ listNode N3 │ (0x300)
                │  "Monday"   │      │ "Wednesday" │      │  "Sunday"   │
                │ link:0x200  │      │ link:0x300  │      │ link: NULL  │
                └─────────────┘      └─────────────┘      └─────────────┘

Print: L = (Monday, Wednesday, Sunday)

──────────────────────────────────────────────────────────────────────────────
2) Search for "Wednesday" node
   Call: p = search_node(L, "Wednesday");
   
   Linear search steps:
   - Start at L->head (Monday) → strcmp("Monday", "Wednesday") ≠ 0
   - Move to next (Wednesday) → strcmp("Wednesday", "Wednesday") == 0 ✓
   - Return pointer to Wednesday node (0x200)

┌─────────────┐
│ linkedList_h│  
│  head: ─────┼───────┐
└─────────────┘       │
                      ▼
                ┌─────────────┐      ┌─────────────┐      ┌─────────────┐
                │ listNode N1 │ ───▶ │ listNode N2 │ ───▶ │ listNode N3 │
                │  "Monday"   │      │ "Wednesday" │      │  "Sunday"   │
                │ link:0x200  │      │ link:0x300  │      │ link: NULL  │
                └─────────────┘      └─────────────┘      └─────────────┘
                                      ▲
                                      │
                                      p (0x200) - Found!

Print: [Wednesday] found !

──────────────────────────────────────────────────────────────────────────────
3) Insert "Friday" after "Wednesday" (middle insertion)
   Call: insert_middle_node(L, p, "Friday");
   Where: p points to "Wednesday" node (0x200)
   
   Steps:
   - Allocate new node N4; N4->data = "Friday"
   - N4->link = p->link (0x300, Sunday node)
   - p->link = N4 (0x400)

Before insertion:
                ┌─────────────┐      ┌─────────────┐      ┌─────────────┐
                │ listNode N1 │ ───▶ │ listNode N2 │ ───▶ │ listNode N3 │
                │  "Monday"   │      │ "Wednesday" │      │  "Sunday"   │
                │ link:0x200  │      │ link:0x300  │      │ link: NULL  │
                └─────────────┘      └─────────────┘      └─────────────┘
                                      ▲
                                      p

After insertion:
┌─────────────┐
│ linkedList_h│  
│  head: ─────┼───────┐
└─────────────┘       │
                      ▼
                ┌─────────────┐      ┌─────────────┐      ┌─────────────┐      ┌─────────────┐
                │ listNode N1 │ ───▶ │ listNode N2 │ ───▶ │ listNode N4 │ ───▶ │ listNode N3 │
                │  "Monday"   │      │ "Wednesday" │      │  "Friday"   │      │  "Sunday"   │
                │ link:0x200  │      │ link:0x400  │      │ link:0x300  │      │ link: NULL  │
                └─────────────┘      └─────────────┘      └─────────────┘      └─────────────┘
                                                            (0x400 - new)

Print: L = (Monday, Wednesday, Friday, Sunday)

──────────────────────────────────────────────────────────────────────────────
4) Delete "Sunday" node
   Call: p = search_node(L, "Sunday");
         delete_node(L, p);
   
   Search result: p = 0x300 (Sunday node)
   
   Delete steps:
   - Find previous node of p (pre = Friday at 0x400)
   - pre->link = p->link (NULL)
   - free(p)

Before deletion:
                ┌─────────────┐      ┌─────────────┐      ┌─────────────┐      ┌─────────────┐
                │ listNode N1 │ ───▶ │ listNode N2 │ ───▶ │ listNode N4 │ ───▶ │ listNode N3 │
                │  "Monday"   │      │ "Wednesday" │      │  "Friday"   │      │  "Sunday"   │
                │ link:0x200  │      │ link:0x400  │      │ link:0x300  │      │ link: NULL  │
                └─────────────┘      └─────────────┘      └─────────────┘      └─────────────┘
                                                            ▲                    ▲
                                                           pre                   p

After deletion:
┌─────────────┐
│ linkedList_h│  
│  head: ─────┼───────┐
└─────────────┘       │
                      ▼
                ┌─────────────┐      ┌─────────────┐      ┌─────────────┐
                │ listNode N1 │ ───▶ │ listNode N2 │ ───▶ │ listNode N4 │
                │  "Monday"   │      │ "Wednesday" │      │  "Friday"   │
                │ link:0x200  │      │ link:0x400  │      │ link: NULL  │
                └─────────────┘      └─────────────┘      └─────────────┘

                ╔═════════════╗
                ║   free N3   ║ (Sunday freed)
                ╚═════════════╝

Print: L = (Monday, Wednesday, Friday)

──────────────────────────────────────────────────────────────────────────────
5) Reverse the list
   Call: reverse(L);
   
   Three-pointer technique:
   Initialize: p = L->head, q = NULL, r = NULL

Iteration 1: (Monday)
  r = q (NULL)
  q = p (Monday)
  p = p->link (Wednesday)
  q->link = r (NULL)

                ┌─────────────┐      ┌─────────────┐      ┌─────────────┐
           NULL ◀─── listNode N1│      │ listNode N2 │ ───▶ │ listNode N4 │
                │  "Monday"   │      │ "Wednesday" │      │  "Friday"   │
                │ link: NULL  │      │ link:0x400  │      │ link: NULL  │
                └─────────────┘      └─────────────┘      └─────────────┘
                 ▲                    ▲
                 q                    p

Iteration 2: (Wednesday)
  r = q (Monday)
  q = p (Wednesday)
  p = p->link (Friday)
  q->link = r (Monday)

                ┌─────────────┐      ┌─────────────┐      ┌─────────────┐
           NULL ◀─── listNode N1│ ◀─── │ listNode N2 │      │ listNode N4 │
                │  "Monday"   │      │ "Wednesday" │      │  "Friday"   │
                │ link: NULL  │      │ link:0x100  │      │ link: NULL  │
                └─────────────┘      └─────────────┘      └─────────────┘
                 ▲                    ▲                    ▲
                 r                    q                    p

Iteration 3: (Friday)
  r = q (Wednesday)
  q = p (Friday)
  p = p->link (NULL)
  q->link = r (Wednesday)

                ┌─────────────┐      ┌─────────────┐      ┌─────────────┐
           NULL ◀─── listNode N1│ ◀─── │ listNode N2 │ ◀─── │ listNode N4 │
                │  "Monday"   │      │ "Wednesday" │      │  "Friday"   │
                │ link: NULL  │      │ link:0x100  │      │ link:0x200  │
                └─────────────┘      └─────────────┘      └─────────────┘
                                      ▲                    ▲
                                      r                    q
                                                           
                                                           p = NULL (exit loop)

Final step: L->head = q (Friday)

┌─────────────┐
│ linkedList_h│  
│  head: ─────┼──────────────────────────────────┐
└─────────────┘                                   │
                                                  ▼
                ┌─────────────┐      ┌─────────────┐      ┌─────────────┐
           NULL ◀─── listNode N1│ ◀─── │ listNode N2 │ ◀─── │ listNode N4 │
                │  "Monday"   │      │ "Wednesday" │      │  "Friday"   │
                │ link: NULL  │      │ link:0x100  │      │ link:0x200  │
                └─────────────┘      └─────────────┘      └─────────────┘

Print: L = (Friday, Wednesday, Monday)

──────────────────────────────────────────────────────────────────────────────
Final: Free all nodes
   Call: free_linked_list(L);
   All nodes freed, list becomes empty
*/