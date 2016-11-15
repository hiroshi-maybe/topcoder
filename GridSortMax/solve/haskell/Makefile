include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/GridSortMaxSolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): GridSortMaxSolver.hs GridSortMax.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

