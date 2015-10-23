include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/CdgameSolver

$(SOLVER): CdgameSolver.go Cdgame/Cdgame.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) CdgameSolver.go 

main: setup $(SOLVER)
