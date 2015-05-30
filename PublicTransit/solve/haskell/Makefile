include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/PublicTransitSolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): PublicTransitSolver.hs PublicTransit.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

