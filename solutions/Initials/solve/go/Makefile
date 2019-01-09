include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/InitialsSolver

$(SOLVER): InitialsSolver.go Initials/Initials.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) InitialsSolver.go 

main: setup $(SOLVER)
