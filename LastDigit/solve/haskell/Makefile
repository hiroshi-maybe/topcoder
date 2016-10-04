include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/LastDigitSolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): LastDigitSolver.hs LastDigit.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

