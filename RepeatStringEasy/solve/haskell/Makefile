include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/RepeatStringEasySolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): RepeatStringEasySolver.hs RepeatStringEasy.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

