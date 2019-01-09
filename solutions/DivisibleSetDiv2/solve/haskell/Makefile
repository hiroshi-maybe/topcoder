include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/DivisibleSetDiv2Solver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): DivisibleSetDiv2Solver.hs DivisibleSetDiv2.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

