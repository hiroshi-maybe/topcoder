include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/DrbalanceSolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): DrbalanceSolver.hs Drbalance.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

