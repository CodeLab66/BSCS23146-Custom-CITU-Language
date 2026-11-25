#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <vector>
using namespace std;

struct Symbol {
    string name;
    string type;
    int scope;
};

// Global Symbol Table variables
extern vector<Symbol> symbolTable;
extern int currentScope;

// Functions
void insertSymbol(string name, string type);
string lookupSymbol(string name);
void printSymbolTable();

#endif