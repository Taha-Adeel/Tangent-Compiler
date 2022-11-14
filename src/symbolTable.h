#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iostream>
#include <string>
#include <map>

enum class SYMBOL_TYPE{
	PRIMITIVE,
	OBJECT,
	TYPENAME,
	FUNCTION,
	UNKNOWN
};

struct YYLTYPE;

/**
 * @brief Symbol table entry
 */
class Symbol{
private:
	std::string name;
	SYMBOL_TYPE type;
	std::string type_name;
	YYLTYPE* location;
	// Properties

public:
	Symbol();
	Symbol(std::string name, SYMBOL_TYPE type = SYMBOL_TYPE::UNKNOWN): name(name), type(type) {}
	
	std::string getName() { return name; }
	SYMBOL_TYPE getType() { return type; }
	std::string getTypeName() { return type_name; }
	YYLTYPE* getLocation() { return location; }

	friend std::ostream& operator << (std::ostream& out, const Symbol& symbol);
};


class SymbolTable{
private:
	std::map<std::string, Symbol> symbol_table;
	std::map<std::string, SymbolTable*> children_symbol_tables;
	SymbolTable* parent = NULL;

public:
	SymbolTable();
	~SymbolTable();

	void addSymbol(Symbol symbol);
	Symbol* lookUpSymbol(std::string name);
	void printSymbolTable();
};

void SymbolTable::addSymbol(Symbol symbol){
	if(lookUpSymbol(symbol.getName()) != NULL){
		throw "Symbol already exists";
	}
	symbol_table[symbol.getName()] = symbol;
}

Symbol* SymbolTable::lookUpSymbol(std::string name){
	if(symbol_table.find(name) != symbol_table.end())
		return &symbol_table[name];
	else if(parent != NULL)
		return parent->lookUpSymbol(name);
	else
		return NULL;
}

void SymbolTable::printSymbolTable(){
	for(auto it = symbol_table.begin(); it != symbol_table.end(); it++){
		std::cout << it->second << std::endl;
	}
}

#endif