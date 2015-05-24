include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/EightRooksSolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): EightRooksSolver.hs EightRooks.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

