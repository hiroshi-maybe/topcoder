include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/BridgeBuildingDiv2Solver

$(SOLVER): BridgeBuildingDiv2Solver.go BridgeBuildingDiv2/BridgeBuildingDiv2.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) BridgeBuildingDiv2Solver.go 

main: setup $(SOLVER)
