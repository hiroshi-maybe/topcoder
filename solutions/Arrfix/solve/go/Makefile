include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/ArrfixSolver

$(SOLVER): ArrfixSolver.go Arrfix/Arrfix.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) ArrfixSolver.go 

main: setup $(SOLVER)
