include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/PartisanGameSolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): PartisanGameSolver.cpp PartisanGame.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
