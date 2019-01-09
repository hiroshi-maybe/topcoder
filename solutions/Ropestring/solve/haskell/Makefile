include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/RopestringSolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): RopestringSolver.hs Ropestring.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

