include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/RandomPancakeStackDiv2Solver

$(SOLVER): RandomPancakeStackDiv2Solver.go RandomPancakeStackDiv2/RandomPancakeStackDiv2.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) RandomPancakeStackDiv2Solver.go 

main: setup $(SOLVER)
