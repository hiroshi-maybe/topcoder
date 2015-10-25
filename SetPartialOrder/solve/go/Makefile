include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/SetPartialOrderSolver

$(SOLVER): SetPartialOrderSolver.go SetPartialOrder/SetPartialOrder.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) SetPartialOrderSolver.go 

main: setup $(SOLVER)
