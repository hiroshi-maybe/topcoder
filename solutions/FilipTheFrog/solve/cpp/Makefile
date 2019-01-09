include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/FilipTheFrogSolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): FilipTheFrogSolver.cpp FilipTheFrog.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
