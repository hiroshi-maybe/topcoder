include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/ChessFloorSolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): ChessFloorSolver.cpp ChessFloor.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
