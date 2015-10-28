include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/CombiningSlimesSolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): CombiningSlimesSolver.hs CombiningSlimes.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

