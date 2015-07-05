include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/BridgeBuildingDiv2Solver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): BridgeBuildingDiv2Solver.hs BridgeBuildingDiv2.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

