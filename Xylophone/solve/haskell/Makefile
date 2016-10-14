include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/XylophoneSolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): XylophoneSolver.hs Xylophone.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

