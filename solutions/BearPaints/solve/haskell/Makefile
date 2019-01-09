include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/BearPaintsSolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): BearPaintsSolver.hs BearPaints.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

