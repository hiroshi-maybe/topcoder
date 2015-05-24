include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/InfiniteStringSolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): InfiniteStringSolver.cpp InfiniteString.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
