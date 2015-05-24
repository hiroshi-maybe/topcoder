include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/CorruptedMessageSolver

$(SOLVER): CorruptedMessageSolver.go CorruptedMessage/CorruptedMessage.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) CorruptedMessageSolver.go 

main: setup $(SOLVER)
