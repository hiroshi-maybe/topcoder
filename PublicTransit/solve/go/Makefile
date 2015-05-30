include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/PublicTransitSolver

$(SOLVER): PublicTransitSolver.go PublicTransit/PublicTransit.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) PublicTransitSolver.go 

main: setup $(SOLVER)
