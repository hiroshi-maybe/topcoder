include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/XMarksTheSpotSolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): XMarksTheSpotSolver.hs XMarksTheSpot.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

