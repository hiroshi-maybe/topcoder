include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/XylophoneSolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): XylophoneSolver.cpp Xylophone.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
