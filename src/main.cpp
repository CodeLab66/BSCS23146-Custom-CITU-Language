#include <iostream>
#include <vector>
#include "lexer.h"
#include "parser.h"

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

    cout << "--- Phase 2: Lexical Analysis ---" << endl;
    tokenize(sourceCode, tokens);
    for (int i = 0; i < tokens.size(); i++) {
        cout << "Token: " << tokens[i].type 
             << " | Value: " << tokens[i].value 
             << " | Line: " << tokens[i].line << endl;
    }

    cout << "\n--- Phase 2: Syntax Analysis ---" << endl;
    parse(tokens);
    cout << "SUCCESS: Code parsed successfully! No syntax errors." << endl;

    return 0;
}