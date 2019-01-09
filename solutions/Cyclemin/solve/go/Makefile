include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/CycleminSolver

$(SOLVER): CycleminSolver.go Cyclemin/Cyclemin.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) CycleminSolver.go 

main: setup $(SOLVER)
