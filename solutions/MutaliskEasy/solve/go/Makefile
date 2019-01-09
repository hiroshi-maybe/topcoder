include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/MutaliskEasySolver

$(SOLVER): MutaliskEasySolver.go MutaliskEasy/MutaliskEasy.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) MutaliskEasySolver.go 

main: setup $(SOLVER)
