include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/UpDownHikingSolver

$(SOLVER): UpDownHikingSolver.go UpDownHiking/UpDownHiking.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) UpDownHikingSolver.go 

main: setup $(SOLVER)
