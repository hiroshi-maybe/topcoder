include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/TriangleMakingSolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): TriangleMakingSolver.hs TriangleMaking.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

