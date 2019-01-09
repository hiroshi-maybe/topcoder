include ../Makefile.common

OUTPUT_D =../../build/go
SOLVER = $(OUTPUT_D)/TaroFillingAStringDiv1Solver

$(SOLVER): TaroFillingAStringDiv1Solver.go TaroFillingAStringDiv1/TaroFillingAStringDiv1.go
	export GOPATH="$$GOPATH:$(GETTC_HOME)/include/go" \
		&& go build -o $(SOLVER) TaroFillingAStringDiv1Solver.go 

main: setup $(SOLVER)
