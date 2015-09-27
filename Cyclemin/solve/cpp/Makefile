include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/CycleminSolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): CycleminSolver.cpp Cyclemin.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
