include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/LiveConcertSolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): LiveConcertSolver.hs LiveConcert.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

