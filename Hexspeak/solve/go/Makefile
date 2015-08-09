include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/HexspeakSolver

$(SOLVER): HexspeakSolver.go Hexspeak/Hexspeak.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) HexspeakSolver.go 

main: setup $(SOLVER)
