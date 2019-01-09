include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/RandomPancakeStackDiv2Solver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): RandomPancakeStackDiv2Solver.cpp RandomPancakeStackDiv2.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
