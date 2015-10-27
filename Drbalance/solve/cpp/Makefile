include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/DrbalanceSolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): DrbalanceSolver.cpp Drbalance.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
