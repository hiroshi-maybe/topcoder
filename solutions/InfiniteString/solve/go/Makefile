include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/InfiniteStringSolver

$(SOLVER): InfiniteStringSolver.go InfiniteString/InfiniteString.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) InfiniteStringSolver.go 

main: setup $(SOLVER)
