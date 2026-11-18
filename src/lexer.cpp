#include "lexer.h"
#include <iostream>
#include <cctype>
#include <cstdlib>

// Global variables for Lexer
int pos = 0;
int currentLine = 1;

char currentChar(string& sourceCode) {
    if (pos >= sourceCode.length()) return '\0';
    return sourceCode[pos];
}

void advance(string& sourceCode) {
    if (currentChar(sourceCode) == '\n') currentLine++;
    pos++;
}

void skipWhitespace(string& sourceCode) {
    while (pos < sourceCode.length() && (currentChar(sourceCode) == ' ' || currentChar(sourceCode) == '\t' || currentChar(sourceCode) == '\r')) {
        advance(sourceCode);
    }
}

void handleIdentifierOrKeyword(string& sourceCode, vector<Token>& tokens) {
    string result = "";
    while (pos < sourceCode.length() && (isalnum(currentChar(sourceCode)) || currentChar(sourceCode) == '_')) {
        result += currentChar(sourceCode);
        advance(sourceCode);
    }

    string type = "ID"; 
    if (result == "jabtak") type = "JABTAK";
    else if (result == "shro") type = "SHRO";
    else if (result == "khtam") type = "KHTAM";
    else if (result == "melado") type = "MELADO";
    else if (result == "int16") type = "INT16";
    else if (result == "int32") type = "INT32";
    else if (result == "uint16") type = "UINT16";
    else if (result == "uint32") type = "UINT32";
    else if (result == "char") type = "CHAR";

    Token t; t.type = type; t.value = result; t.line = currentLine;
    tokens.push_back(t);
}

void handleNumber(string& sourceCode, vector<Token>& tokens) {
    string result = "";
    while (pos < sourceCode.length() && isdigit(currentChar(sourceCode))) {
        result += currentChar(sourceCode);
        advance(sourceCode);
    }
    Token t; t.type = "LT"; t.value = result; t.line = currentLine;
    tokens.push_back(t);
}

void tokenize(string sourceCode, vector<Token>& tokens) {
    pos = 0; 
    currentLine = 1; 
    tokens.clear();

    while (pos < sourceCode.length()) {
        skipWhitespace(sourceCode);
        if (pos >= sourceCode.length()) break;

        char c = currentChar(sourceCode);

        if (c == '/' && pos + 1 < sourceCode.length() && sourceCode[pos + 1] == '/') {
            while (pos < sourceCode.length() && currentChar(sourceCode) != '\n') advance(sourceCode);
            continue;
        }

        if (isalpha(c) || c == '_') {
            handleIdentifierOrKeyword(sourceCode, tokens);
        } else if (c == '\n') {
            advance(sourceCode); // Just skip the newline and move to the next line
        } else if (isdigit(c)) {
            handleNumber(sourceCode, tokens);
        } else if (c == '+') { advance(sourceCode); Token t; t.type="PLUS"; t.value="+"; t.line=currentLine; tokens.push_back(t); }
        else if (c == '-') { advance(sourceCode); Token t; t.type="MINUS"; t.value="-"; t.line=currentLine; tokens.push_back(t); }
        else if (c == '*') { advance(sourceCode); Token t; t.type="MULT"; t.value="*"; t.line=currentLine; tokens.push_back(t); }
        else if (c == '/') { advance(sourceCode); Token t; t.type="DIV"; t.value="/"; t.line=currentLine; tokens.push_back(t); }
        else if (c == '(') { advance(sourceCode); Token t; t.type="LPAREN"; t.value="("; t.line=currentLine; tokens.push_back(t); }
        else if (c == ')') { advance(sourceCode); Token t; t.type="RPAREN"; t.value=")"; t.line=currentLine; tokens.push_back(t); }
        else {
            cout << "Lexer Error: Unknown character '" << c << "' at line " << currentLine << endl;
            exit(1);
        }
    }
    Token t; t.type = "EOF"; t.value = "EOF"; t.line = currentLine;
    tokens.push_back(t);
}