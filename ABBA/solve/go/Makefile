include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/ABBASolver

$(SOLVER): ABBASolver.go ABBA/ABBA.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) ABBASolver.go 

main: setup $(SOLVER)
