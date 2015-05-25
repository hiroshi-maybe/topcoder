include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/ProblemSetsEasySolver

$(SOLVER): ProblemSetsEasySolver.go ProblemSetsEasy/ProblemSetsEasy.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) ProblemSetsEasySolver.go 

main: setup $(SOLVER)
