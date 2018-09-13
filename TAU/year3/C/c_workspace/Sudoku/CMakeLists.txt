cmake_minimum_required(VERSION 3.12)
project(Sudoku C)
set(CMAKE_C_STANDARD 11)
#add_custom_target(sudoku-console COMMAND make -C ${sudoku_SOURCE_DIR} BLDDIR=${PROJECT_BINARY_DIR})

#cmake_minimum_required(VERSION 3.12)
#project(Sudoku C)
#
#set(CMAKE_C_STANDARD 11)
#
include_directories(.)
#



add_executable(Sudoku
        FileManager.c
        FileManager.h
        Game.c
        Game.h
        ILPSolver.c
        ILPSolver.h
        LinkedList.c
        LinkedList.h
        main.c
        Parser.c
        Parser.h
        Solver.c
        Solver.h)
target_include_directories(Sudoku PUBLIC /Library/gurobi563/mac64/include/)
target_link_libraries(Sudoku /Library/gurobi563/mac64/lib/libgurobi56.so)
