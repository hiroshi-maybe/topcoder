include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/GridSortMaxSolver

$(SOLVER): GridSortMaxSolver.go GridSortMax/GridSortMax.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) GridSortMaxSolver.go 

main: setup $(SOLVER)
