include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/UpDownHikingSolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): UpDownHikingSolver.hs UpDownHiking.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

