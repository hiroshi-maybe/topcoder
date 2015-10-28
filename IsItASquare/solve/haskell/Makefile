include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/IsItASquareSolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): IsItASquareSolver.hs IsItASquare.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

