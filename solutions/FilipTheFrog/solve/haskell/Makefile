include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/FilipTheFrogSolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): FilipTheFrogSolver.hs FilipTheFrog.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

