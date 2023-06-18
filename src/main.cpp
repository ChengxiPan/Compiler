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
  filenames.push_back("./rules/Sys.java");
  filenames.push_back("./rules/Math.java");
  filenames.push_back("./rules/Array.java");
  filenames.push_back("./rules/Memory.java");
  filenames.push_back("./rules/String.java");
  filenames.push_back("./rules/Output.java");
  filenames.push_back("./rules/Input.java");
  filenames.push_back("./rules/IO.java");
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
