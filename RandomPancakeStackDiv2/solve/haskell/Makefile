include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/RandomPancakeStackDiv2Solver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): RandomPancakeStackDiv2Solver.hs RandomPancakeStackDiv2.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

