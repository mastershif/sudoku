//
// Created by Shif on 20/08/2018.
//

#ifndef SUDOKU_LINKEDLIST_H
#define SUDOKU_LINKEDLIST_H

typedef struct node_t {
    int X;
    int Y;
    int value;
    int prev_value;
    struct node_t* next;
    struct node_t* prev;
} Node;

Node* createNewNode(int X, int Y, int value, int prev_value);

Node* InsertAtHead(int X, int Y, int value, int prev_value, Node* head);

#endif //SUDOKU_NODE_H
