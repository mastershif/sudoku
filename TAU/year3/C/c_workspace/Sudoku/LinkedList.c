#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "LinkedList.h"

//Creates a new node and returns a pointer to it.
Node* createNewNode(int X, int Y, int value, int prev_value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("the createNewNode malloc failed :( \n");
        return NULL;
    }
    new_node->X = X;
    new_node->Y = Y;
    new_node->value = value;
    new_node->prev_value = prev_value;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

// Inserts a node at start of a doubly linked list
Node* InsertAtHead(int X, int Y, int value, int prev_value, Node* head) {
    printf("was ordered to insert move node with x = %d, y = %d, value = %d\n", X, Y, value);
    Node* newNode = createNewNode(X, Y, value, prev_value);
    printf("newNode was created with x = %d, y = %d, value = %d\n", newNode->X, newNode->Y, newNode->value);
    if (head == NULL) {
        printf("no moves exist! making this move the head of game->moves\n");
//        head = (Node *)calloc(1, sizeof(Node));
//	    if(head == NULL) {
//		    printf("Error: could not callocate memory for moves\n");
//		    exit(1);
//	    }
        head = newNode;
        return head;
    }
    head->next = newNode;
    newNode->prev = head;
    head = newNode;
    return head;
}
