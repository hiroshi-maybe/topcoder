include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/MutaliskEasySolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): MutaliskEasySolver.hs MutaliskEasy.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

