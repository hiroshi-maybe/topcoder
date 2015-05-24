include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/EightRooksSolver

$(SOLVER): EightRooksSolver.go EightRooks/EightRooks.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) EightRooksSolver.go 

main: setup $(SOLVER)
