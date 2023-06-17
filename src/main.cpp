#include "Analyzer.h"
#include "CodeGen.h"
#include "Parser.h"
#include "Scanner.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "usage: " << argv[0] << " <filename, filename ... >" << endl;
    exit(-1);
  }
  ifstream fin;
  vector<string> filenames;
  for (int i = 1; i < argc; i++) {
    fin.open(argv[i]);
    if (fin.fail()) {
      cerr << "file '" << argv[i] << "' not exist!";
      exit(-1);
    }
    filenames.push_back(argv[i]);
    fin.close();
  }
  filenames.push_back("./api/Sys.java");
  filenames.push_back("./api/Math.java");
  filenames.push_back("./api/Array.java");
  filenames.push_back("./api/Memory.java");
  filenames.push_back("./api/String.java");
  filenames.push_back("./api/Output.java");
  filenames.push_back("./api/Input.java");
  filenames.push_back("./api/IO.java");
  Parser parser(filenames);
  parser.parse_program();
  if (!hasError()) {
    Analyzer analyzer(parser.getSyntaxTree());
    analyzer.check();
  }
  if (!hasError()) {
    CodeGen cgen;
    cgen.write(parser.getSyntaxTree());
  }

  return 0;
}
