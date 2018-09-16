CC = gcc
OBJS = Game.o Parser.o Solver.o FileManager.o LinkedList.o ILPSolver.o main.o
EXEC = SUDOKU
COMP_FLAG = -std=c99 -Wall -Wextra -Werror -Wno-implicit -pedantic-errors -I/usr/local/lib/gurobi563/include -g

BLDDIR = build


$(BLDDIR)/sudoku-console: $(BLDDIR)/main.o $(BLDDIR)/FileManager.o $(BLDDIR)/Game.o $(BLDDIR)/Parser.o $(BLDDIR)/Solver.o $(BLDDIR)/LinkedList.o $(BLDDIR)/ILPSolver.o
	@echo " CC " $@
	@mkdir -p $(dir $@)
	$(CC) -o $(BLDDIR)/sudoku-console $(BLDDIR)/main.o $(BLDDIR)/FileManager.o $(BLDDIR)/Game.o $(BLDDIR)/Parser.o $(BLDDIR)/Solver.o $(BLDDIR)/LinkedList.o $(BLDDIR)/ILPSolver.o -L/usr/local/lib/gurobi563/lib -lm -lpthread -lgurobi56 -g


$(BLDDIR)/main.o: main.c
	@echo " CC " $@
	@mkdir -p $(dir $@)
	$(CC) $(COMP_FLAG) -c main.c -o $(BLDDIR)/main.o

$(BLDDIR)/FileManager.o: FileManager.c FileManager.h
	@echo " CC " $@
	@mkdir -p $(dir $@)
	$(CC) $(COMP_FLAG) -c FileManager.c -o $(BLDDIR)/FileManager.o

$(BLDDIR)/Game.o: Game.c Game.h
	@echo " CC " $@
	@mkdir -p $(dir $@)
	$(CC) $(COMP_FLAG) -c Game.c -o $(BLDDIR)/Game.o

$(BLDDIR)/Parser.o: Parser.c Parser.h
	@echo " CC " $@
	@mkdir -p $(dir $@)
	$(CC) $(COMP_FLAG) -c Parser.c -o $(BLDDIR)/Parser.o

$(BLDDIR)/Solver.o: Solver.c Solver.h
	@echo " CC " $@
	@mkdir -p $(dir $@)
	$(CC) $(COMP_FLAG) -c Solver.c -o $(BLDDIR)/Solver.o

$(BLDDIR)/LinkedList.o: LinkedList.c LinkedList.h
	@echo " CC " $@
	@mkdir -p $(dir $@)
	$(CC) $(COMP_FLAG) -c LinkedList.c -o $(BLDDIR)/LinkedList.o

$(BLDDIR)/ILPSolver.o: ILPSolver.c ILPSolver.h
	@echo " CC " $@
	@mkdir -p $(dir $@)
	$(CC) $(COMP_FLAG) -c ILPSolver.c -o $(BLDDIR)/ILPSolver.o

clean:
	rm -f $(BLDDIR)/*.o $(EXEC)
