#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iostream>
#include <string>
#include <map>

enum class SYMBOL_TYPE{
	PRIMITIVE,
	OBJECT,
	INBUILT_TYPENAME,
	TYPENAME,
	FUNCTION,
	UNKNOWN
};

struct YYLTYPE;

class Symbol{
private:
	std::string name;
	SYMBOL_TYPE type;
	std::string type_name;
	YYLTYPE* location;
	// Properties

public:
	Symbol();
	Symbol(std::string name, SYMBOL_TYPE type, std::string type_name, YYLTYPE* location)
		:name(name), type(type), type_name(type_name), location(location) {}
	
	std::string getName() { return name; }
	SYMBOL_TYPE getType() { return type; }
	std::string getTypeName() { return type_name; }
	YYLTYPE* getLocation() { return location; }

	friend std::ostream& operator << (std::ostream& out, const Symbol& symbol);
};

class SymbolTable{
private:
	std::string namespace_name;
	std::map<std::string, Symbol> symbol_table;
	std::map<std::string, SymbolTable*> child_symbol_tables;
	SymbolTable* parent = NULL;

private:
	void createObjectSymbolTable(std::string object_name, std::string type_name);

public:
	static bool insideVariableDeclaration;
	static std::string currentVariableType;

public:
	SymbolTable(SymbolTable* parent, std::string namespace_name = "");
	~SymbolTable();

	void addSymbol(std::string identifier_name, std::string type_name, YYLTYPE* location, SYMBOL_TYPE type = SYMBOL_TYPE::UNKNOWN);
	Symbol* lookUp(std::string name);
	void printSymbolTable(int indentation = 0);
};

SymbolTable::SymbolTable(SymbolTable* parent, std::string _namespace_name)
	:parent(parent), namespace_name(_namespace_name) 
{
	if(parent == NULL) {
		namespace_name = "global";
	}
	if(namespace_name == "")
		namespace_name = parent->namespace_name + "::" + to_string(child_symbol_tables.size());
}

void SymbolTable::addSymbol(std::string identifier_name, std::string type_name, YYLTYPE* location, SYMBOL_TYPE type){
	if(type == SYMBOL_TYPE::UNKNOWN){
		Symbol* type_name_symbol = lookUp(type_name);
		if(type_name_symbol == NULL)
			throw "Type name not found: " + type_name;
		switch(type_name_symbol->getType()){
			case SYMBOL_TYPE::INBUILT_TYPENAME: 
				type = SYMBOL_TYPE::PRIMITIVE; 
				break;
			case SYMBOL_TYPE::TYPENAME: 
				type = SYMBOL_TYPE::OBJECT;
				createObjectSymbolTable(identifier_name, type_name);
				break;
			default: 
				throw "Invalid type name: " + type_name;
		}
	}
	// TODO: Create new symbol table for functions

	if(lookUp(identifier_name) != NULL)
		throw "Identifier already declared: " + identifier_name;
	symbol_table[identifier_name] = Symbol(identifier_name, type, type_name, location);
}

Symbol* SymbolTable::lookUp(std::string name){
	if(symbol_table.find(name) != symbol_table.end())
		return &symbol_table[name];
	else if(parent != NULL)
		return parent->lookUp(name);
	else
		return NULL;
}

void SymbolTable::createObjectSymbolTable(std::string object_name, std::string type_name){
	Symbol* type_name_symbol = lookUp(type_name);
	if(type_name_symbol == NULL)
		throw "Type name not found: " + type_name;
	if(type_name_symbol->getType() != SYMBOL_TYPE::TYPENAME)
		throw "Type name is not a typename: " + type_name;
	SymbolTable* object_symbol_table = new SymbolTable(this, object_name);
	// TODO: Add all the members of the class/family to the symbol table
	child_symbol_tables[object_name] = object_symbol_table;
}

void SymbolTable::printSymbolTable(int indentation){
	for(int i = 0; i < indentation; i++)
		std::cout << "\t";
	std::cout << "Symbol Table: " << namespace_name << std::endl;
	for(auto symbol : symbol_table){
		for(int i = 0; i < indentation; i++)
			std::cout << "\t";
		std::cout << symbol.second << std::endl;
	}
	for(auto child_symbol_table : child_symbol_tables){
		child_symbol_table.second->printSymbolTable(indentation + 1);
	}
}

#endif