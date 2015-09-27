include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/ChessFloorSolver

$(SOLVER): ChessFloorSolver.go ChessFloor/ChessFloor.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) ChessFloorSolver.go 

main: setup $(SOLVER)
