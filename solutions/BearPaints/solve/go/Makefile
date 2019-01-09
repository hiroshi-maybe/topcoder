include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/BearPaintsSolver

$(SOLVER): BearPaintsSolver.go BearPaints/BearPaints.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) BearPaintsSolver.go 

main: setup $(SOLVER)
