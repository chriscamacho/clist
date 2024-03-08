
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "clist.h"

#define MAX_ITEMS 20

// usually you would create more substantial list members!
typedef struct {
    int value;
} item;

void printNode(cnode_t* node)
{
    item* i = (item*)node->data;
    int v = i->value;
    printf("%i, ", v);
}

int cmpNode(cnode_t* node1, cnode_t* node2)
{
    item* i1 = (item*)node1->data;
    int v1 = i1->value;
    item* i2 = (item*)node2->data;
    int v2 = i2->value;
    return v1 - v2;
}

int revCmpNode(cnode_t* node1, cnode_t* node2)
{
    item* i1 = (item*)node1->data;
    int v1 = i1->value;
    item* i2 = (item*)node2->data;
    int v2 = i2->value;
    return v2 - v1;
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    clist_t* theList = clistCreateList();
    printf("List created\n");
       
    for (int i=0; i < MAX_ITEMS; i++) {
        item* i = calloc(1, sizeof(item));
        if (i) {
            i->value = rand() % 10;
        } else {
            printf("Unable to allocate memory for item!\n");
            exit(-1);
        }
        clistAddNode(theList, i);
    }
    
    printf("iterate forward\n");
    clistIterateForward(theList, printNode);
    
    printf("\niterate backward\n");
    clistIterateBackward(theList, printNode);
    printf("\n");
    
    printf("sort list\n");
    clistSort(theList, cmpNode);
    clistIterateForward(theList, printNode);
    printf("\n");
    
    printf("The list has %i items\n", clistTotal(theList));
    printf("removing every other item\n");
    
    // manual list iteration
    bool del = false;
    cnode_t* next = theList->head;
    
    while(next) {
        cnode_t* current = next;
        // get the next *before* possibly deleting the current
        next = current->next;
        if (del) {
            free(current->data);
            clistDeleteNode(theList, &current);
        }
        del = !del;
    }
    
    printf("The list has %i items\n", clistTotal(theList));
    clistIterateForward(theList, printNode);
    printf("\n");
    printf("sort high to low\n");
    clistSort(theList, revCmpNode);
    clistIterateForward(theList, printNode);
    printf("\n");
        
    printf("freeing all list items\n");
    next = theList->head;
    while(next) {
        cnode_t* current = next;
        // get the next *before* deleting the current
        next = current->next;
        free(current->data);
        clistDeleteNode(theList, &current);
    }
    // list still usable here
    
    clistFreeList(&theList);
    
    printf("The end \n");
    
    return(0);
}
