#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "gurobi_c.h"
#include "ILPSolver.h"

void copySolutionToResults(int N, double *solution, int** results) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                if (solution[i * N * N + j * N + k] == 1) {
                    results[i][j] = k + 1;
                }
            }
        }
    }
}

/*
 * The sudoku board is a NxN grid, which is further divided into a nxm grid
 * of mxn grids.
 * Each cell in the grid must take a value from 0 to N.
 * No two grid cells in the same row, column, or mxn subgrid may take the same value.
 *
 * In the Mixed Integer Programming formulation, the variables are binary.
 * Each variable x[i,j,v] indicate whether cell (i,j) takes value 'v'.
 *
 * These are the constraints in the model:
 * 1. Each cell must take exactly one value (sum_v x[i,j,v] = 1)
 * 2. Each value is used exactly once per row (sum_i x[i,j,v] = 1)
 * 3. Each value is used exactly once per column (sum_j x[i,j,v] = 1)
 * 4. Each value is used exactly once per mxn subgrid (sum_grid x[i,j,v] = 1)
 */

int solveWithILP(int m, int n, int **gameBoard, int** results) {

    int N = m * n;
    int error = 0;
    int i, j, v, ig, jg, count;
    int optimization_status;

    GRBenv* env = NULL;
    GRBmodel* model = NULL;

    int *constraint1_indices, *constraint2_indices;
    constraint1_indices = (int *) malloc(N * sizeof(int));
    constraint2_indices = (int *) malloc(N * sizeof(int));

    double *solution, *val1, *val2, *lower_bounds;
    solution = (double *) malloc(N * N * N * sizeof(double));
    val1 = (double *) malloc(N * sizeof(double));
    val2 = (double *) malloc(N * sizeof(double));
    lower_bounds = (double *) malloc(N * N * N * sizeof(double));

    double objval;

    char *var_type;
    var_type = (char *) malloc(N * N * N * sizeof(char));

    // create an empty model
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (v = 0; v < N; v++) {
                if (gameBoard[i][j] == v + 1) {
                    lower_bounds[i * N * N + j * N + v] = 1;
                } else {
                    lower_bounds[i * N * N + j * N + v] = 0;
                }
                var_type[i * N * N + j * N + v] = GRB_BINARY;
            }
        }
    }

    // create environment
    error = GRBloadenv(&env, "sudoku.log");
    if (error) {
        printf("ERROR %d GRBloadenv(): %s\n", error, GRBgeterrormsg(env));
        freeModel(solution, constraint1_indices, constraint2_indices, val1, val2, lower_bounds, var_type, env, model);
        return 1;
    }

    // create a new model
    error = GRBnewmodel(env, &model, "sudoku", N * N * N, NULL, lower_bounds, NULL,
                        var_type, NULL);
    if (error) {
        printf("ERROR %d GRBnewmodel(): %s\n", error, GRBgeterrormsg(env));
        freeModel(solution, constraint1_indices, constraint2_indices, val1, val2, lower_bounds, var_type, env, model);
        return 1;
    }

    // add constraints to the model

    // each cell must get a value
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (v = 0; v < N; v++) {
                constraint1_indices[v] = i * N * N + j * N + v;
                val1[v] = 1.0;
            }
            error = GRBaddconstr(model, N, constraint1_indices, val1, GRB_EQUAL, 1.0, NULL);
            if (error) {
                printf("ERROR %d GRBaddconstr() for 1st constraint: %s\n", error, GRBgeterrormsg(env));
                freeModel(solution, constraint1_indices, constraint2_indices, val1, val2, lower_bounds, var_type, env, model);
                return 1;
            }
        }
    }

    // if cell value is not 0 then this value will remain
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (gameBoard[i][j] != 0) {
                constraint2_indices[0] = i * N * N + j * N + (gameBoard[i][j] - 1);
                val2[0] = 1;
                error = GRBaddconstr(model, 1, constraint2_indices, val2, GRB_EQUAL, 1.0, NULL);
                if (error) {
                    printf("ERROR %d GRBaddconstr() for 2nd constraint: %s\n", error, GRBgeterrormsg(env));
                    freeModel(solution, constraint1_indices, constraint2_indices, val1, val2, lower_bounds, var_type, env, model);
                    return 1;
                }
            }
        }
    }

    // each value must appear exactly once in each row
    for (v = 0; v < N; v++) {
        for (j = 0; j < N; j++) {
            for (i = 0; i < N; i++) {
                constraint1_indices[i] = i * N * N + j * N + v;
                val1[i] = 1.0;
            }

            error = GRBaddconstr(model, N, constraint1_indices, val1, GRB_EQUAL, 1.0, NULL);
            if (error) {
                printf("ERROR %d GRBaddconstr() for 3rd constraint: %s\n", error, GRBgeterrormsg(env));
                freeModel(solution, constraint1_indices, constraint2_indices, val1, val2, lower_bounds, var_type, env, model);
                return 1;
            }
        }
    }

    // each value must appear exactly once in each column
    for (v = 0; v < N; v++) {
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                constraint1_indices[j] = i * N * N + j * N + v;
                val1[j] = 1.0;
            }

            error = GRBaddconstr(model, N, constraint1_indices, val1, GRB_EQUAL, 1.0, NULL);
            if (error) {
                printf("ERROR %d GRBaddconstr() for 4th constraint: %s\n", error, GRBgeterrormsg(env));
                freeModel(solution, constraint1_indices, constraint2_indices, val1, val2, lower_bounds, var_type, env, model);
                return 1;
            }
        }
    }

    // each value must appear exactly once in each box
    // n  number of boxes vertically
    // m  number of boxes horizontally
    for (v = 0; v < N; v++) { // which box
        for (ig = 0; ig < n; ig++) {
            for (jg = 0; jg < m; jg++) {
                count = 0;
                // iterates over the cells in that block
                for (i = ig * m; i < (ig + 1) * m; i++) {
                    for (j = jg * n; j < (jg + 1) * n; j++) {
                        constraint1_indices[count] = i * N * N + j * N + v;
                        val1[count] = 1.0;
                        count++;
                    }
                }
                error = GRBaddconstr(model, N, constraint1_indices, val1, GRB_EQUAL, 1.0, NULL);
                if (error) {
                    printf("ERROR %d GRBaddconstr() for 5th constraint: %s\n", error, GRBgeterrormsg(env));
                    freeModel(solution, constraint1_indices, constraint2_indices, val1, val2, lower_bounds, var_type, env, model);
                    return 1;
                }
            }
        }
    }

    // run the gurobi optimization
    error = GRBoptimize(model);
    if (error) {
        printf("ERROR %d GRBoptimize(): %s\n", error, GRBgeterrormsg(env));
        freeModel(solution, constraint1_indices, constraint2_indices, val1, val2, lower_bounds, var_type, env, model);
        return 1;
    }

    // write the model to a file named sudoku.lp
    error = GRBwrite(model, "sudoku.lp");
    if (error) {
        printf("ERROR %d GRBwrite(): %s\n", error, GRBgeterrormsg(env));
        freeModel(solution, constraint1_indices, constraint2_indices, val1, val2, lower_bounds, var_type, env, model);
        return 1;
    }

    // get solution information
    error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimization_status);
    if (error) {
        printf("ERROR %d GRBgetintattr(): %s\n", error, GRBgeterrormsg(env));
        freeModel(solution, constraint1_indices, constraint2_indices, val1, val2, lower_bounds, var_type, env, model);
        return 1;
    }

    // get the objective -- the optimal result of the function
    error = GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &objval);
    if (error) {
        printf("ERROR %d GRBgettdblattr(): %s\n", error, GRBgeterrormsg(env));
        freeModel(solution, constraint1_indices, constraint2_indices, val1, val2, lower_bounds, var_type, env, model);
        return 1;
    }

    // get the solution - the assignment to each variable
    // N * N * N - number of variables, the size of "solution" should match
    error = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, N * N * N, solution);
    if (error) {
        printf("ERROR %d GRBgetdblattrarray(): %s\n", error, GRBgeterrormsg(env));
        freeModel(solution, constraint1_indices, constraint2_indices, val1, val2, lower_bounds, var_type, env, model);
        return 1;
    }

    copySolutionToResults(N, solution, results);

    freeModel(solution, constraint1_indices, constraint2_indices, val1, val2, lower_bounds, var_type, env, model);

    return 0;
}

void freeModel(double *solution, int *constraint1_indices, int *constraint2_indices,
        double *val1, double *val2, double *lower_bounds, char *var_type, GRBenv *env,
        GRBmodel *model) {
    free(solution);
    free(constraint1_indices);
    free(constraint2_indices);
    free(val1);
    free(val2);
    free(lower_bounds);
    free(var_type);
    GRBfreemodel(model);
    GRBfreeenv(env);
}
