include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/PrivateD2partySolver

$(SOLVER): PrivateD2partySolver.go PrivateD2party/PrivateD2party.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) PrivateD2partySolver.go 

main: setup $(SOLVER)
