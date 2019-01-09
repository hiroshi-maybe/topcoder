include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/IsItASquareSolver

$(SOLVER): IsItASquareSolver.go IsItASquare/IsItASquare.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) IsItASquareSolver.go 

main: setup $(SOLVER)
