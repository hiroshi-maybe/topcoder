include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/PrivateD2partySolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): PrivateD2partySolver.hs PrivateD2party.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

