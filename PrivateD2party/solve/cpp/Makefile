include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/PrivateD2partySolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): PrivateD2partySolver.cpp PrivateD2party.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
