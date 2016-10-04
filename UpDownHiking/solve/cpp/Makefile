include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/UpDownHikingSolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): UpDownHikingSolver.cpp UpDownHiking.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
