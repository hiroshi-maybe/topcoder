include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/FilipTheFrogSolver

$(SOLVER): FilipTheFrogSolver.go FilipTheFrog/FilipTheFrog.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) FilipTheFrogSolver.go 

main: setup $(SOLVER)
