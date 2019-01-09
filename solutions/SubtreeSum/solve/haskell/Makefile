include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/SubtreeSumSolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): SubtreeSumSolver.hs SubtreeSum.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

