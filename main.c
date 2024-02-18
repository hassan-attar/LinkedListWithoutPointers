#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    int next_index;
    int prev_index;
};

struct LinkedList {
    struct Node *nodes;
    int head_index;
    int tail_index;
    int free_index;
    int capacity;
};

/**
 * Init. the LinkedList struct, to a certain capacity, init the singly linkedList of freeSpace (behaves as Stack)
 * @param ll the linkedList struct
 * @param cap capacity
 */
void initialize(struct LinkedList *ll, int cap){
    ll->nodes = (struct Node *)malloc(sizeof(struct Node) * cap);
    ll->head_index = -1;
    ll->tail_index = -1;
    ll->free_index = 0;
    for(int i = 0; i < cap; i++){
        ll->nodes[i].next_index = i + 1;
    }
    ll->nodes[cap - 1].next_index = -1;
    ll->capacity = cap;
}

/**
 * Inserts element to the end of the LinkedList (after the tail)
 * @param ll the linkedList struct
 * @param data data to be inserted
 * @return true if operation was successful, false otherwise
 */
int push_back(struct LinkedList *ll, int data){
    if(ll->free_index == -1){
        printf("No more empty space\n");
        return 0; // no more free space
    }
    if(ll->head_index == -1){ // empty list
        ll->head_index = ll->tail_index = ll->free_index; //   -1 <- NewNode(head, tail) -> -1
        ll->free_index = ll->nodes[ll->free_index].next_index;
        ll->nodes[ll->head_index].data = data;
        ll->nodes[ll->head_index].prev_index = -1;
        ll->nodes[ll->head_index].next_index = -1;
    } else {
        ll->nodes[ll->free_index].data = data; //   OldTail -> NewNode(Tail) -> -1
        ll->nodes[ll->free_index].prev_index = ll->tail_index;
        ll->nodes[ll->tail_index].next_index = ll->free_index;
        ll->tail_index = ll->free_index;
        ll->free_index = ll->nodes[ll->free_index].next_index;
        ll->nodes[ll->tail_index].next_index = -1;
    }
    return 1;
}

/**
 * Inserts element to the start of the LinkedList (before the head)
 * @param ll the linkedList struct
 * @param data data to be inserted
 * @return true if operation was successful, false otherwise
 */
int push_front(struct LinkedList *ll, int data){
    if(ll->free_index == -1){
        printf("No more empty space\n");
        return 0; // no more free space
    }
    if(ll->head_index == -1){ // empty list
        ll->head_index = ll->tail_index = ll->free_index; //   -1 <- NewNode(head, tail) -> -1
        ll->free_index = ll->nodes[ll->free_index].next_index;
        ll->nodes[ll->head_index].data = data;
        ll->nodes[ll->head_index].prev_index = -1;
        ll->nodes[ll->head_index].next_index = -1;
    } else {
        // using head->prev as temp variable
        ll->nodes[ll->free_index].data = data;  //  -1 <- NewNode(head) -> OldHead
        ll->nodes[ll->head_index].prev_index = ll->free_index;
        ll->free_index = ll->nodes[ll->free_index].next_index;
        ll->nodes[ll->nodes[ll->head_index].prev_index].next_index = ll->head_index;
        ll->head_index = ll->nodes[ll->head_index].prev_index;
        ll->nodes[ll->head_index].prev_index = -1;
    }
    return 1;
}

/**
 * finds the index of the element within the linkedList
 * @param ll the linkedList struct
 * @param data data to be searched for
 * @return index of the node in the linkedList, -1 if not found
 */
int search(struct LinkedList *ll, int data){
    int index = ll->head_index;
    while(index != -1 && ll->nodes[index].data != data){
        index = ll->nodes[index].next_index;
    }
    return index;
}

/**
 * Removes element from the end of the LinkedList (tail)
 * @param ll the linkedList struct
 * @return true if operation was successful, false otherwise
 */
int pop_back(struct LinkedList *ll){
    if(ll->head_index == -1){
        return 0; // popping from an empty list
    }else if(ll->head_index == ll->tail_index){ // last node
        ll->nodes[ll->head_index].next_index = ll->free_index;
        ll->free_index = ll->head_index;
        ll->head_index = ll->tail_index = -1;
    } else {
        ll->nodes[ll->tail_index].next_index = ll->free_index;
        ll->free_index = ll->tail_index;
        ll->tail_index = ll->nodes[ll->tail_index].prev_index;
        ll->nodes[ll->tail_index].next_index = -1;
    }
    return 1;
}

/**
 * Removes element from the start of the LinkedList (head)
 * @param ll the linkedList struct
 * @return true if operation was successful, false otherwise
 */
int pop_front(struct LinkedList *ll){
    if(ll->head_index == -1){
        return 0; // popping from an empty list
    }else if(ll->head_index == ll->tail_index){ // last node
        ll->nodes[ll->head_index].next_index = ll->free_index;
        ll->free_index = ll->head_index;
        ll->head_index = ll->tail_index = -1;
    } else {
        ll->head_index = ll->nodes[ll->head_index].next_index;
        ll->nodes[ll->nodes[ll->head_index].prev_index].next_index = ll->free_index;
        ll->free_index = ll->nodes[ll->head_index].prev_index;
        ll->nodes[ll->head_index].prev_index = -1;
    }
    return 1;
}

/**
 * Removes element holding data
 * @param ll the linkedList struct
 * @return true if operation was successful, false otherwise
 */
int remove_node(struct LinkedList *ll, int data){
    if(ll->head_index == -1){
        return 0; // popping from an empty list
    }else{
        int index = search(ll, data);
        if(index == -1){
            return 0; // element not there
        }else if(index == ll->head_index){
            return pop_front(ll);
        }else if(index == ll->tail_index){
            return pop_back(ll);
        }else{
            ll->nodes[ll->nodes[index].prev_index].next_index = ll->nodes[index].next_index;
            ll->nodes[ll->nodes[index].next_index].prev_index = ll->nodes[index].prev_index;
            ll->nodes[index].next_index = ll->free_index;
            ll->free_index = index;
        }
    }
    return 1;
}

/**
 * Inserts node at a specific place within the LinkedList
 * @param ll the LinkedList struct
 * @param index the index to be inserted at, 0 means before Head, -1 after tail
 * @param data to be inserted
 * @return true if operation was successful, false otherwise
 */
int insert_node(struct LinkedList *ll, int index, int data){
    if(ll->free_index == -1) return 0; // no more free space
    int i = ll->head_index;
    if(index == 0) return push_front(ll, data);
    while(i != -1 && index > 1){
        index--;
        i = ll->nodes[i].next_index;
    }
    if(i == -1) return push_back(ll, data);
    ll->nodes[ll->free_index].data = data;  // i -> newNode -> i's Next
    ll->nodes[ll->free_index].prev_index = i;
    ll->nodes[ll->nodes[i].next_index].prev_index = ll->free_index;
    ll->free_index = ll->nodes[ll->free_index].next_index;
    ll->nodes[ll->nodes[ll->nodes[i].next_index].prev_index].next_index = ll->nodes[i].next_index;
    ll->nodes[i].next_index = ll->nodes[ll->nodes[i].next_index].prev_index;
    return 1;
}

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}
/**
 * Prints the LinkedList from head to tail.
 * @param ll LinkedList struct
 */
void printLinkedList(struct LinkedList *ll){
    int index = ll->head_index;
    printf("Head -> ");
    while(index != -1){
        printf("%d -> ", ll->nodes[index].data);
        index = ll->nodes[index].next_index;
    }
    printf("Tail\n");
}

/**
 * Prints the LinkedList from tail to head.
 * @param ll LinkedList struct
 */
void printLinkedListReverse(struct LinkedList *ll){
    int index = ll->tail_index;
    printf("Tail -> ");
    while(index != -1){
        printf("%d -> ", ll->nodes[index].data);
        index = ll->nodes[index].prev_index;
    }
    printf("Head\n");
}

/**
 * Prints the underlying array behind the LinkedList and the free list (memory layout)
 * @param ll LinkedList struct
 * @param size size of the LinkedList to be printed (you can pass capacity if you want the whole layout)
 */
void printWholeLinkedListDS(struct LinkedList *ll, int size){
    int index = 0;
    printf("%-6s", "Index:");
    printf("|");
    int i;
    for(i = 0; i < size; i++){
        printf("%-4d|", i);
    }
    printf("\n%-6s", "Next:");
    printf("|");
    for(i = 0; i < size; i++){
        printf("%-4d|", ll->nodes[i].next_index);
    }
    printf("\n%-6s", "Data:");
    printf("|");
    for(i = 0; i < size; i++){
        printf("%-4d|", ll->nodes[i].data);
    }
    printf("\n%-6s", "Prev:");
    printf("|");
    for(i = 0; i < size; i++){
        printf("%-4d|", ll->nodes[i].prev_index);
    }
    printf("\n%-7s", " ");
    for(i = 0; i < size; i++){
        if(i == ll->head_index){
            printf("%-4s|", "head");
        }else if(i == ll->tail_index){
            printf("%-4s|", "tail");
        }else if(i == ll->free_index){
            printf("%-4s|", "free");
        }else {
            printf("%-4s|", " ");
        }
    }

    printf("\n");
}

/**
 * This operation will move all the allocated object to the beginning on the memory array.
 * assuming that you want to copy the data, or trying to find a contiguous chunk of memory, or other purposes.
 * the idea is to move all the allocated objects together, in a contiguous memory layout
 * @idea It works by partitioning the list, based on a cutOffPoint, which is the maximum index that will be occupied by the linkedList objects
 * It will only move the nodes that are after that cutOffPoint, which makes it very efficient (we have to move those anyway)
 * The time complexity is linear
 * @param ll the linkedList struct
 */
void compactifyList(struct LinkedList *ll){
    int cutOffPoint = 0;
    int i = ll->head_index;
    while(i != -1){ // O(n)
        cutOffPoint++;
        i = ll->nodes[i].next_index;
    }
    // any node greater than or equal to pivot most move to the left side of pivot.
    // any empty space less than pivot, must move to the right side of pivot
    int l = ll->head_index, r = ll->free_index;
    while (1){ // O(n) Worst Case
        while(l!= -1 && l < cutOffPoint){
            l = ll->nodes[l].next_index;
        }
        while(r >= cutOffPoint){
            r = ll->nodes[r].next_index;
        }
        if(l == -1 || r == -1) break; // we are done as soon as there is no empty space to the left, or no object to the right of the cutOffPoint
        // printf("Nodes to be swapped are index %d, index %d\n", l, r);
        ll->nodes[r].data = ll->nodes[l].data;
        if(ll->nodes[l].next_index != -1)
            ll->nodes[ll->nodes[l].next_index].prev_index = r;
        if(ll->nodes[l].prev_index != -1)
            ll->nodes[ll->nodes[l].prev_index].next_index = r;
        ll->nodes[r].prev_index = ll->nodes[l].prev_index;
        swap(&ll->nodes[r].next_index, &ll->nodes[l].next_index);
        if(l == ll->head_index){
            ll->head_index = r;
        }
        if(l == ll->tail_index){
            ll->tail_index = r;
        }
        swap(&l, &r);
    }
    ll->free_index = cutOffPoint;
    for(i = cutOffPoint; i < ll->capacity - 1; i++){
        ll->nodes[i].next_index = i + 1;
    }
    ll->nodes[i].next_index = -1;
}


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
    printLinkedList(&ll);
    printWholeLinkedListDS(&ll, size);
    printLinkedListReverse(&ll);

    return 0;
}
