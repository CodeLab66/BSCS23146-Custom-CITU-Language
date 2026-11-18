#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
using namespace std;

// Token Structure
struct Token {
    string type;
    string value;
    int line;
};

// Lexer Function
void tokenize(string sourceCode, vector<Token>& tokens);

#endif