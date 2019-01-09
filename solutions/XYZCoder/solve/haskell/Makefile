include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/XYZCoderSolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): XYZCoderSolver.hs XYZCoder.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

