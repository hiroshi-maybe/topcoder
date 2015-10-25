include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/BearDartsDiv2Solver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): BearDartsDiv2Solver.hs BearDartsDiv2.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

