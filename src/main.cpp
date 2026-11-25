#include <iostream>
#include <vector>
#include "lexer.h"
#include "parser.h"
#include "symbol_table.h"

using namespace std;

int main() {
    string sourceCode = R"(
    int16 x
    int16 y
    x melado 10
    jabtak (x) shro
        y melado x * 5
        x melado x - 1
    khtam
    )";

    vector<Token> tokens;

    cout << "--- Phase 3: Lexical Analysis ---" << endl;
    tokenize(sourceCode, tokens);
    
    for (int i = 0; i < tokens.size(); i++) {
        cout << "Line " << tokens[i].line << " | Type: " << tokens[i].type 
             << " | Value: '" << tokens[i].value << "'" << endl;
    }

    cout << "\n--- Phase 3: Syntax & Semantic Analysis ---" << endl;
    parse(tokens);
    cout << "SUCCESS: Code parsed and semantically verified!" << endl;

    printSymbolTable(); 

    return 0;
}