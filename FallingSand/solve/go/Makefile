include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/FallingSandSolver

$(SOLVER): FallingSandSolver.go FallingSand/FallingSand.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) FallingSandSolver.go 

main: setup $(SOLVER)
