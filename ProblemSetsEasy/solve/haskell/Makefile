include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/ProblemSetsEasySolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): ProblemSetsEasySolver.hs ProblemSetsEasy.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

