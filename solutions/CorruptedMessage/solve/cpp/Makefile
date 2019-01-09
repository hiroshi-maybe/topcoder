include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/CorruptedMessageSolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): CorruptedMessageSolver.cpp CorruptedMessage.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
