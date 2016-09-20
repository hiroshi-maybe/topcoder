include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/RepeatStringEasySolver

$(SOLVER): RepeatStringEasySolver.go RepeatStringEasy/RepeatStringEasy.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) RepeatStringEasySolver.go 

main: setup $(SOLVER)
