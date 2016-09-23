include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/TriangleMakingSolver

$(SOLVER): TriangleMakingSolver.go TriangleMaking/TriangleMaking.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) TriangleMakingSolver.go 

main: setup $(SOLVER)
