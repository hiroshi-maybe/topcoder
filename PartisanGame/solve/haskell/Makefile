include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/PartisanGameSolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): PartisanGameSolver.hs PartisanGame.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

