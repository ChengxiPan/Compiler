clean:
	rm -f *.o
Lexical:
	g++ -o TokenGet.o Scanner.h Scanner.cpp Lexicalt.cpp
	./TokenGet.o exec
Parser:
	g++ -o Parser.o Scanner.h Scanner.cpp Parser.h Parser.cpp Parsert.cpp
	./Parser.o exec
Analyzer:
	g++ -o main.o Scanner.h Scanner.cpp Error.h Error.cpp Parser.h Parser.cpp Analyzer.h Analyzer.cpp SymbolTable.h SymbolTable.cpp CodeGen.h CodeGen.cpp main.cpp
	./main.o Main.java