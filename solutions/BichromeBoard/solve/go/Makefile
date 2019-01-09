include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/BichromeBoardSolver

$(SOLVER): BichromeBoardSolver.go BichromeBoard/BichromeBoard.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) BichromeBoardSolver.go 

main: setup $(SOLVER)
