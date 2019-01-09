include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/RepeatStringEasySolver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): RepeatStringEasySolver.cpp RepeatStringEasy.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
