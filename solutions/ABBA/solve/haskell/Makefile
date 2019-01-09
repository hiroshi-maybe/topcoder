include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/ABBASolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): ABBASolver.hs ABBA.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

