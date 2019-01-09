include ../Makefile.common

OUTPUT_D = ../../build/haskell
SOLVER = $(OUTPUT_D)/CorruptedMessageSolver
COMPILER = ghc -i$(GETTC_HOME)/include/haskell -outputdir $(OUTPUT_D)

$(SOLVER): CorruptedMessageSolver.hs CorruptedMessage.hs
	$(COMPILER) -o $(SOLVER) $<

main: setup $(SOLVER)

