include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/ArrfixSolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): ArrfixSolver.hs Arrfix.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

