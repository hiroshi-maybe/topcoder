include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/SetPartialOrderSolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): SetPartialOrderSolver.hs SetPartialOrder.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

