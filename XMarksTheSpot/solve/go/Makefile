include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/XMarksTheSpotSolver

$(SOLVER): XMarksTheSpotSolver.go XMarksTheSpot/XMarksTheSpot.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) XMarksTheSpotSolver.go 

main: setup $(SOLVER)
