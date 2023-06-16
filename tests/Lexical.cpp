#include "Scanner.h"
#include <iostream>

using namespace std;

int main() {
  Scanner scanner;
  scanner.openFile("src/test.jack");
  Scanner::Token token = scanner.nextToken();
  while (token.kind != Scanner::ENDOFFILE) {
    cout << "[Token]: " << token.lexeme << " [Kind]: " << token.kind << endl;
    token = scanner.nextToken();
  }
  scanner.closeFile();
  return 0;
}