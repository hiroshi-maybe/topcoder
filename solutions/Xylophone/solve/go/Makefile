include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/XylophoneSolver

$(SOLVER): XylophoneSolver.go Xylophone/Xylophone.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) XylophoneSolver.go 

main: setup $(SOLVER)
