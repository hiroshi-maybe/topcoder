include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/RopestringSolver

$(SOLVER): RopestringSolver.go Ropestring/Ropestring.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) RopestringSolver.go 

main: setup $(SOLVER)
