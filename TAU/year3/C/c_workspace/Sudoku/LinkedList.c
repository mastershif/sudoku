#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "LinkedList.h"
#include "Game.h"

//Creates a new node and returns a pointer to it.
Node* createNewNode(int **gameBoard,int rows, int cols) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("the createNewNode malloc failed :( \n");
        return NULL;
    }
    new_node->board = copyBoard(gameBoard, rows, cols);
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

int freeLinkedList(Node* listStart, int N) {
    Node* currentNode = listStart;
    Node* temp;
    int countOfNodesFreed = 0;

    while (currentNode != NULL) {
        temp = currentNode;
        currentNode = currentNode->next;
        // also free the board of the node:
        if (temp->board != NULL) {
            for (int i = 0; i < N; i++) {
                free(temp->board[i]);
            }
            free(temp->board);
        }
        free(temp);
        countOfNodesFreed++;
    }
    return countOfNodesFreed;
}
