include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/SubtreeSumSolver

$(SOLVER): SubtreeSumSolver.go SubtreeSum/SubtreeSum.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) SubtreeSumSolver.go 

main: setup $(SOLVER)
