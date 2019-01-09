include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/DrbalanceSolver

$(SOLVER): DrbalanceSolver.go Drbalance/Drbalance.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) DrbalanceSolver.go 

main: setup $(SOLVER)
