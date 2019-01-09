include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/PartisanGameSolver

$(SOLVER): PartisanGameSolver.go PartisanGame/PartisanGame.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) PartisanGameSolver.go 

main: setup $(SOLVER)
