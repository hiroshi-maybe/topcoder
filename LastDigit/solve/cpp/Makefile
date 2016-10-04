include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/LastDigitSolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): LastDigitSolver.cpp LastDigit.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
