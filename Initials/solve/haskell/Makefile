include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/InitialsSolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): InitialsSolver.hs Initials.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

