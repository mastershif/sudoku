//
// Created by Shif on 20/08/2018.
//

#ifndef SUDOKU_LINKEDLIST_H
#define SUDOKU_LINKEDLIST_H

/**
 * This module defines and deals with linked lists.
 */

typedef struct node_t {
    int **board;
    struct node_t* next;
    struct node_t* prev;
} Node;

/**
 * Creates a new Node that can be part of a linked list.
 *
 * @param gameBoard - the board that the newly created node will contain a copy of.
 * @param rows - the number of rows in the board.
 * @param cols - the number of columns in the board
 * @return
 * Returns the newly created board.
 */
Node* createNewNode(int **gameBoard, int rows, int cols);

/**
 * Free all of the nodes in a linked list starting from the parameter listStart.
 * Free the nodes and also their content.
 *
 * @param listStart - the node where the freeing starts.
 * @param N - the number of rows in the board in each node in the list.
 * @return
 * Returns the number of freed nodes.
 */
int freeLinkedList(Node* listStart, int N);

#endif //SUDOKU_NODE_H
