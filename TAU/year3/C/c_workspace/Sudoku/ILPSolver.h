#ifndef SUDOKU_ILPSOLVER_H
#define SUDOKU_ILPSOLVER_H

#include "gurobi_c.h"

int solve(int m, int n, int **gameBoard);

int solveWithILP(int m, int n, int **gameBoard, int** results);

void freeModel(double *solution, int *constraint1_indices, int *constraint2_indices,
               double *val1, double *val2, double *lower_bounds, char *var_type, GRBenv *env,
               GRBmodel *model);

#endif //SUDOKU_ILPSOLVER_H
