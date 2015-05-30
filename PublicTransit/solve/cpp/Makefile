include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/PublicTransitSolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): PublicTransitSolver.cpp PublicTransit.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
