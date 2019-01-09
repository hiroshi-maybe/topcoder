include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/GridSortMaxSolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): GridSortMaxSolver.cpp GridSortMax.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
