include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/CombiningSlimesSolver

$(SOLVER): CombiningSlimesSolver.go CombiningSlimes/CombiningSlimes.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) CombiningSlimesSolver.go 

main: setup $(SOLVER)
