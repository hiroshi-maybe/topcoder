include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/ProblemSetsEasySolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): ProblemSetsEasySolver.cpp ProblemSetsEasy.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
