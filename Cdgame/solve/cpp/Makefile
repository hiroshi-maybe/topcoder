include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/CdgameSolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): CdgameSolver.cpp Cdgame.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
