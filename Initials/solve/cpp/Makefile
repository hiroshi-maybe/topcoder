include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/InitialsSolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): InitialsSolver.cpp Initials.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
