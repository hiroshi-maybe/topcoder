include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/DivisibleSetDiv2Solver

$(SOLVER): DivisibleSetDiv2Solver.go DivisibleSetDiv2/DivisibleSetDiv2.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) DivisibleSetDiv2Solver.go 

main: setup $(SOLVER)
