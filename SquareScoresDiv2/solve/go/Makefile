include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/SquareScoresDiv2Solver

$(SOLVER): SquareScoresDiv2Solver.go SquareScoresDiv2/SquareScoresDiv2.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) SquareScoresDiv2Solver.go 

main: setup $(SOLVER)
