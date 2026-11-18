#include "parser.h"
#include <iostream>
#include <cstdlib>

// Global variables for Parser
int tokenPos = 0;
Token currentToken;
vector<Token> allTokens;

void getNextToken() {
    if (tokenPos < allTokens.size()) {
        currentToken = allTokens[tokenPos];
        tokenPos++;
    }
}

void error(string msg) {
    cout << "Parser Error: " << msg << " at line " << currentToken.line << endl;
    exit(1);
}

void eat(string type) {
    if (currentToken.type == type) {
        getNextToken();
    } else {
        error("Expected " + type + " but got " + currentToken.type);
    }
}

// Forward declarations
void program(); void st(); void ws(); void cst(); void slist(); 
void ds(); void as_stmt(); void ex(); void ex_prime(); void t(); void t_prime(); void f();

void program() {
    while (currentToken.type != "EOF") { st(); }
}

void st() {
    if (currentToken.type == "JABTAK") ws();
    else if (currentToken.type == "SHRO") cst();
    else if (currentToken.type == "ID") as_stmt();
    else if (currentToken.type == "INT16" || currentToken.type == "INT32" ||
             currentToken.type == "UINT16" || currentToken.type == "UINT32" ||
             currentToken.type == "CHAR") ds();
    else error("Unexpected token in statement: " + currentToken.type);
}

void ws() { eat("JABTAK"); eat("LPAREN"); ex(); eat("RPAREN"); cst(); }
void cst() { eat("SHRO"); slist(); eat("KHTAM"); }

void slist() {
    while (currentToken.type == "JABTAK" || currentToken.type == "SHRO" ||
           currentToken.type == "ID" || currentToken.type == "INT16" ||
           currentToken.type == "INT32" || currentToken.type == "UINT16" ||
           currentToken.type == "UINT32" || currentToken.type == "CHAR") {
        st();
    }
}

void ds() { eat(currentToken.type); eat("ID"); }
void as_stmt() { eat("ID"); eat("MELADO"); ex(); }

void ex() { t(); ex_prime(); }
void ex_prime() {
    if (currentToken.type == "PLUS") { eat("PLUS"); t(); ex_prime(); }
    else if (currentToken.type == "MINUS") { eat("MINUS"); t(); ex_prime(); }
}

void t() { f(); t_prime(); }
void t_prime() {
    if (currentToken.type == "MULT") { eat("MULT"); f(); t_prime(); }
    else if (currentToken.type == "DIV") { eat("DIV"); f(); t_prime(); }
}

void f() {
    if (currentToken.type == "ID") eat("ID");
    else if (currentToken.type == "LT") eat("LT");
    else if (currentToken.type == "LPAREN") { eat("LPAREN"); ex(); eat("RPAREN"); }
    else error("Unexpected token in factor: " + currentToken.type);
}

void parse(vector<Token> tokens) {
    allTokens = tokens;
    tokenPos = 0;
    getNextToken();
    program();
}