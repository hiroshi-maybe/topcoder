include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/XMarksTheSpotSolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): XMarksTheSpotSolver.cpp XMarksTheSpot.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
