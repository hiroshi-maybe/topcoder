include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/IsItASquareSolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): IsItASquareSolver.cpp IsItASquare.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
