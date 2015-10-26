include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/LiveConcertSolver

$(SOLVER): LiveConcertSolver.go LiveConcert/LiveConcert.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) LiveConcertSolver.go 

main: setup $(SOLVER)
