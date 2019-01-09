include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/SquareScoresDiv2Solver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): SquareScoresDiv2Solver.cpp SquareScoresDiv2.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
