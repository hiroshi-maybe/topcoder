include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/HexspeakSolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): HexspeakSolver.hs Hexspeak.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

