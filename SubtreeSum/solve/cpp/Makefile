include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/SubtreeSumSolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): SubtreeSumSolver.cpp SubtreeSum.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
