include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/DivisibleSetDiv2Solver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): DivisibleSetDiv2Solver.cpp DivisibleSetDiv2.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
