include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/BridgeBuildingDiv2Solver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): BridgeBuildingDiv2Solver.cpp BridgeBuildingDiv2.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
