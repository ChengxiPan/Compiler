#include "Parser.h"
#include "Scanner.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
  ifstream fin;
  vector<string> filenames;
  filenames.push_back("../rules/Sys.java");
  filenames.push_back("../rules/Math.java");
  filenames.push_back("../rules/Array.java");
  filenames.push_back("../rules/Memory.java");
  filenames.push_back("../rules/String.java");
  filenames.push_back("../rules/Output.java");
  filenames.push_back("../rules/Input.java");
  filenames.push_back("../rules/IO.j");
  // Parser parser(filenames);
  // parser.parse_program();
  return 0;
}
