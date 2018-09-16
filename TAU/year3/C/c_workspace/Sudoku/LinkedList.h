//
// Created by Shif on 20/08/2018.
//

#ifndef SUDOKU_LINKEDLIST_H
#define SUDOKU_LINKEDLIST_H

typedef struct node_t {
    int **board;
    struct node_t* next;
    struct node_t* prev;
} Node;

Node* createNewNode(int **gameBoard, int rows, int cols);

int freeLinkedList(Node* listStart, int N);

#endif //SUDOKU_NODE_H
