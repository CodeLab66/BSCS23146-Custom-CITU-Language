#include "symbol_table.h"
#include <iostream>

using namespace std;

vector<Symbol> symbolTable;
int currentScope = 0;

void insertSymbol(string name, string type) {
    // Check for redeclaration in the CURRENT scope only
    for (int i = symbolTable.size() - 1; i >= 0; i--) {
        if (symbolTable[i].name == name && symbolTable[i].scope == currentScope) {
            cout << "Semantic Error: Variable '" << name << "' is already declared in this scope." << endl;
            exit(1);
        }
    }

    Symbol s;
    s.name = name;
    s.type = type;
    s.scope = currentScope;
    symbolTable.push_back(s);
}

string lookupSymbol(string name) {
    // Search backwards to handle scoping (inner scopes shadow outer scopes)
    for (int i = symbolTable.size() - 1; i >= 0; i--) {
        if (symbolTable[i].name == name) {
            return symbolTable[i].type;
        }
    }
    return "UNDEFINED";
}

void printSymbolTable() {
    cout << "\n--- Symbol Table ---" << endl;
    cout << "Name\tType\tScope" << endl;
    for (int i = 0; i < symbolTable.size(); i++) {
        cout << symbolTable[i].name << "\t" << symbolTable[i].type << "\t" << symbolTable[i].scope << endl;
    }
    cout << "--------------------" << endl;
}