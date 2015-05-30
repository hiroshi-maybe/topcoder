include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/SquareScoresDiv2Solver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): SquareScoresDiv2Solver.hs SquareScoresDiv2.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

