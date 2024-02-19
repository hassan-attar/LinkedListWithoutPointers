# C Linked List Implementation

This repository contains a C implementation of a linked list using arrays. It provides various operations for manipulating the linked list, such as insertion, deletion, searching, and compactification.
This is based on chapter 10, section 3 (10.3) of the CLRS book (Introduction to Algorithm).
## Features

- **Initialization**: Initialize a linked list with a specified capacity.
- **Insertion**: Insert elements at the beginning, end, or at a specific index of the linked list.
- **Deletion**: Remove elements from the beginning, end, or at a specific index of the linked list.
- **Search**: Find the index of an element within the linked list.
- **Compactification**: Rearrange the nodes within the array to eliminate gaps and ensure a contiguous sequence of nodes.

## Usage

To use this linked list implementation:

1. Clone or download this repository to your local machine.
2. Include the `LinkedList.h` header file in your project.
3. Compile your project along with the `LinkedList.c` source file with the following command:
```bash
gcc -o prog main.c LinkedList.c
```

## Visuals:
you can use `printWholeLinkedListDS` function, to have visual on the underlying array (memory).
#### **Examples:**
```c
#include "LinkedList.h"
#include <stdio.h>
int main() {
    struct LinkedList ll;
    int size = 12;
    initialize(&ll, size);
    push_back(&ll, 40);
    push_back(&ll, 50);
    push_back(&ll, 60);
    push_front(&ll, 20);
    push_front(&ll, 10);
    insert_node(&ll, 2, 30);
    pop_back(&ll);
    pop_back(&ll);

    remove_node(&ll, search(&ll, 50));
    remove_node(&ll, search(&ll, 80));
    printLinkedList(&ll);
    printWholeLinkedListDS(&ll, size);
    printLinkedListReverse(&ll);
    compactifyList(&ll);
    printf("\n--------------After Compactify: \n\n");
    printLinkedList(&ll);
    printWholeLinkedListDS(&ll, size);
    printLinkedListReverse(&ll);

    return 0;
}
```
#### **Output:**
<pre>
Head -> 10 -> 20 -> 30 -> 40 -> Tail
Index:|0   |1   |2   |3   |4   |5   |6   |7   |8   |9   |10  |11  |
Next: |-1  |2   |6   |5   |3   |0   |7   |8   |9   |10  |11  |-1  |
Data: |40  |50  |60  |20  |10  |30  |0   |0   |0   |0   |0   |0   |
Prev: |5   |0   |1   |4   |-1  |3   |0   |0   |0   |0   |0   |0   |
       tail|free|    |    |head|    |    |    |    |    |    |    |
Tail -> 40 -> 30 -> 20 -> 10 -> Head

--------------After Compactify: 

Head -> 10 -> 20 -> 30 -> 40 -> Tail
Index:|0   |1   |2   |3   |4   |5   |6   |7   |8   |9   |10  |11  |
Next: |-1  |3   |0   |2   |5   |6   |7   |8   |9   |10  |11  |-1  |
Data: |40  |10  |30  |20  |10  |30  |0   |0   |0   |0   |0   |0   |
Prev: |2   |-1  |3   |1   |-1  |3   |0   |0   |0   |0   |0   |0   |
       tail|head|    |    |free|    |    |    |    |    |    |    |
Tail -> 40 -> 30 -> 20 -> 10 -> Head

</pre>

## Examples:
```c
#include <stdio.h>
#include "LinkedList.h"

int main() {
    struct LinkedList ll;
    int size = 12;
    initialize(&ll, size);
    push_back(&ll, 40);
    push_back(&ll, 50);
    push_back(&ll, 60);
    // Other operations...
    return 0;
}

```
