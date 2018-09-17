#ifndef SUDOKU_ILPSOLVER_H
#define SUDOKU_ILPSOLVER_H

#include "gurobi_c.h"

/**
 * This module uses the Gurobi optimizer to solve sudoku boards.
 */

/**
* Solves a sudoku boardand store the resulting solution in @param results.
*
* @param m - the number of rows in each box in the sudoku board.
* @param n - the number of columns in each box in the sudoku board.
* @param gameBoard - the sudoku board to be solved.
* @param results - where the solution is stored.
* @return
* 1 if the solving failed ata ny stage,
* 0 is a solution was found successfully.
*/
int solveWithILP(int m, int n, int **gameBoard, int** results);

/**
* Free the Gurobi model and all of its resources, to be used after running solveWithILP.
*
* @param solution - a resource used by the Gurobi model.
* @param constraint1_indices - a resource used by the Gurobi model.
* @param constraint2_indices - a resource used by the Gurobi model.
* @param val1 - a resource used by the Gurobi model.
* @param val2 - a resource used by the Gurobi model.
* @param lower_bounds - a resource used by the Gurobi model.
* @param var_type - a resource used by the Gurobi model.
* @param env - a resource used by the Gurobi model.
* @param model - a resource used by the Gurobi model.
*/
void freeModel(double *solution, int *constraint1_indices, int *constraint2_indices,
               double *val1, double *val2, double *lower_bounds, char *var_type, GRBenv *env,
               GRBmodel *model);

#endif //SUDOKU_ILPSOLVER_H
