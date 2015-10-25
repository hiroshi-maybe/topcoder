include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/SetPartialOrderSolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): SetPartialOrderSolver.cpp SetPartialOrder.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
