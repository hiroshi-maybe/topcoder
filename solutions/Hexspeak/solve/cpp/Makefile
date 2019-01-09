include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/HexspeakSolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): HexspeakSolver.cpp Hexspeak.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
