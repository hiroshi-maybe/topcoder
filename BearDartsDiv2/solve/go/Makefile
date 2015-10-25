include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/BearDartsDiv2Solver

$(SOLVER): BearDartsDiv2Solver.go BearDartsDiv2/BearDartsDiv2.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) BearDartsDiv2Solver.go 

main: setup $(SOLVER)
