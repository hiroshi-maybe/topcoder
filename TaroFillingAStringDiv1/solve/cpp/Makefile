include ../Makefile.common

OUTPUT_D =../../build/cpp
SOLVER = $(OUTPUT_D)/TaroFillingAStringDiv1Solver
COMPILER = g++ -std=gnu++0x -I$(GETTC_HOME)/include/cpp

$(SOLVER): TaroFillingAStringDiv1Solver.cpp TaroFillingAStringDiv1.cpp
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)
