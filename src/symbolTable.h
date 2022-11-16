#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <variant>
#include <optional>

enum class TYPE {INT, FLOAT, STRING, BOOL, FAMILY, ERROR, VOID, POINT, PATH, IMAGE, RECTANGLE, CIRCLE, ELLIPSE, POLYGON, CURVE, PI, COLOUR}; 
class Family
{
    std::string name;
    std::map<std::string, int> int_members;
    std::map<std::string, float> float_members;
    std::map<std::string, string> string_members;
    std::map<std::string, bool> bool_members;
    std::map<std::string, Family> family_members;
};
/// @brief a token class to represent error in eval function
class error{};
typedef variant<int, float, string, bool, Family, error> datatype;

/**
 * @brief Enum representing the different types of symbols
 * 
 */
enum class SYMBOL_TYPE{
	PRIMITIVE,
	OBJECT,
	INBUILT_TYPENAME,
	TYPENAME,
	FUNCTION,
	UNKNOWN
};

struct YYLTYPE;

/**
 * @brief Represents an entry in a Symbol Table
 * 
 * A symbol table entry holds the identifier name, type of symbol, the typename of the symbol,
 * and its location where it was declared
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
	Symbol(std::string name, SYMBOL_TYPE type, std::string type_name, YYLTYPE* location)
		:name(name), type(type), type_name(type_name), location(location) {}
	
	std::string getName() { return name; }
	SYMBOL_TYPE getType() { return type; }
	std::string getTypeName() { return type_name; }
	YYLTYPE* getLocation() { return location; }

	friend std::ostream& operator << (std::ostream& out, const Symbol& symbol);
};

/**
 * @brief Represents a Symbol Table
 *
 * Internally uses a map to store the symbols. Each symbol table can have multiple child symbol tables, 
 * to represent nested scopes and such.
 */
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

/**
 * @brief Construct a new Symbol Table::Symbol Table object
 * 
 * @param parent The parent symbol table
 * @param namespace_name 
 */
SymbolTable::SymbolTable(SymbolTable* parent, std::string _namespace_name)
	:parent(parent), namespace_name(_namespace_name) 
{
	if(parent == NULL) {
		namespace_name = "global";
	}
	if(namespace_name == "")
		namespace_name = parent->namespace_name + "::" + to_string(child_symbol_tables.size());
}

/**
 * @brief Adds a new symbol to the symbol table when it is declared
 * 
 * @param identifier_name 
 * @param type_name 
 * @param location 
 * @param type 
 */
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

/**
 * @brief Searches for the identifier in the symbol table (and in its parent symbol tables)
 * 
 * @param name Identifier name
 * @return Symbol* Returns NULL if "name" not found in the symbol table
 */
Symbol* SymbolTable::lookUp(std::string name){
	if(symbol_table.find(name) != symbol_table.end())
		return &symbol_table[name];
	else if(parent != NULL)
		return parent->lookUp(name);
	else
		return NULL;
}

/**
 * @brief Creates a new Symbol Table for an object and adds it to the child symbol tables
 * 
 * @param object_name object_name
 * @param type_name class/family name
 */
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

/**
 * @brief Utility function to display the symbol table
 * Prints each symbol table with its namespace name, followed by its child symbol tables
 */
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