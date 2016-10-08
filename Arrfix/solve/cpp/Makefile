include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/ArrfixSolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): ArrfixSolver.cpp Arrfix.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
