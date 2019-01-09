include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/XYZCoderSolver

$(SOLVER): XYZCoderSolver.go XYZCoder/XYZCoder.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) XYZCoderSolver.go 

main: setup $(SOLVER)
