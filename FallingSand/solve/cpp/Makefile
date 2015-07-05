include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/FallingSandSolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): FallingSandSolver.cpp FallingSand.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
