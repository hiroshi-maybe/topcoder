include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/ChessFloorSolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): ChessFloorSolver.hs ChessFloor.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

