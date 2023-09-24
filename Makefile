.PHONY: buildopt debug
.DEFAULT_GOAL := buildopt

buildopt:
	g++ -O3 -o test test.cpp RabinKarp.cpp

debug:
	g++ -O0 -g -o test test.cpp RabinKarp.cpp