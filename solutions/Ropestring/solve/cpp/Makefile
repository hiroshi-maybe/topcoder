include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/RopestringSolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): RopestringSolver.cpp Ropestring.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
