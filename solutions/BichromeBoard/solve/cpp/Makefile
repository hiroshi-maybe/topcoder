include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/BichromeBoardSolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): BichromeBoardSolver.cpp BichromeBoard.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
