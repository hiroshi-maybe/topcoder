include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/LastDigitSolver

$(SOLVER): LastDigitSolver.go LastDigit/LastDigit.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) LastDigitSolver.go 

main: setup $(SOLVER)
