#include "symbolTable.h"

typedef struct YYLTYPE
{
	int first_line;
	int first_column;
	int last_line;
	int last_column;
	const char *filename;
} YYLTYPE;

std::ostream& operator << (std::ostream& os, const YYLTYPE* loc){
	if(loc == NULL) return os << "Inbuilt symbol";
	return os << loc->filename << ": (" << loc->first_line << ":" << loc->first_column << ")-(" << loc->last_line << ":" << loc->last_column << ")";
}

/**
 * @brief Overloading << to print a symbol
 * 
 * @param out 
 * @param symbol 
 * @return std::ostream& 
 */
std::ostream& operator << (std::ostream& out, const Symbol& symbol){
	out << "Symbol: " << symbol.name << " Type Name: " << symbol.type_name << " Location: " << (symbol.location);
	return out;
}

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
		addInbuiltSymbols();
	}
	if(namespace_name == "")
		namespace_name = parent->namespace_name + "::" + std::to_string(child_symbol_tables.size());
}
std::string SymbolTable::currentVariableType = "";

/**
 * @brief Prepopulate the symbol table with inbuilt symbols provided by our language
 * 
 */
void SymbolTable::addInbuiltSymbols(){
	addInbuiltPrimitiveTypenames();
	addInbuiltFamilyTypenames();
	addInbuiltFunctions();
	addInbuiltConstants();
}

/**
 * @brief Add the inbuilt primitive typenames such as int, float, string, bool and void
 * 
 */
void SymbolTable::addInbuiltPrimitiveTypenames(){
	addSymbol("int", "int", NULL, SYMBOL_TYPE::INBUILT_PRIMITIVE_TYPENAME);
	addSymbol("float", "float", NULL, SYMBOL_TYPE::INBUILT_PRIMITIVE_TYPENAME);
	addSymbol("string", "string", NULL, SYMBOL_TYPE::INBUILT_PRIMITIVE_TYPENAME);
	addSymbol("bool", "bool", NULL, SYMBOL_TYPE::INBUILT_PRIMITIVE_TYPENAME);
	addSymbol("void", "void", NULL, SYMBOL_TYPE::INBUILT_PRIMITIVE_TYPENAME);
}

/**
 * @brief Add the inbuilt family typenames such as Point, Path, Image, Rectangle, Circle, Ellipse, Polygon, Curve, Color
 * 
 */
void SymbolTable::addInbuiltFamilyTypenames(){
	addSymbol("Point", "Point", NULL, SYMBOL_TYPE::INBUILT_FAMILY_TYPENAME);
	addSymbol("Path", "Path", NULL, SYMBOL_TYPE::INBUILT_FAMILY_TYPENAME);
	addSymbol("Image", "Image", NULL, SYMBOL_TYPE::INBUILT_FAMILY_TYPENAME);
	addSymbol("Rectangle", "Rectangle", NULL, SYMBOL_TYPE::INBUILT_FAMILY_TYPENAME);
	addSymbol("Circle", "Circle", NULL, SYMBOL_TYPE::INBUILT_FAMILY_TYPENAME);
	addSymbol("Ellipse", "Ellipse", NULL, SYMBOL_TYPE::INBUILT_FAMILY_TYPENAME);
	addSymbol("Polygon", "Polygon", NULL, SYMBOL_TYPE::INBUILT_FAMILY_TYPENAME);
	addSymbol("Curve", "Curve", NULL, SYMBOL_TYPE::INBUILT_FAMILY_TYPENAME);
	addSymbol("Color", "Color", NULL, SYMBOL_TYPE::INBUILT_FAMILY_TYPENAME);

	// TODO: Create a new symbol table for each of the family types and add the inbuilt functions and constants
}

/**
 * @brief Add the inbuilt functions such as print, draw, etc. 
 * 
 */
void SymbolTable::addInbuiltFunctions(){
	addSymbol("print", "void", NULL, SYMBOL_TYPE::INBUILT_FUNCTION);
	addSymbol("draw", "void", NULL, SYMBOL_TYPE::INBUILT_FUNCTION);
}

/**
 * @brief Add the inbuilt constants such as Pi, etc. 
 * 
 */
void SymbolTable::addInbuiltConstants(){
	addSymbol("Pi", "float", NULL, SYMBOL_TYPE::PRIMITIVE_VAR);
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
		if(type_name_symbol == NULL){
			std::cerr << std::string("Error: Type name not found: " + type_name) << std::endl;
			type_name = "error-type";
		}
		else switch(type_name_symbol->getType()){
			case SYMBOL_TYPE::INBUILT_PRIMITIVE_TYPENAME: 
				type = SYMBOL_TYPE::PRIMITIVE_VAR; 
				break;
			case SYMBOL_TYPE::INBUILT_FAMILY_TYPENAME:
			case SYMBOL_TYPE::FAMILY_TYPENAME:
				type = SYMBOL_TYPE::OBJECT_VAR;
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
	if(type_name_symbol->getType() != SYMBOL_TYPE::FAMILY_TYPENAME)
		throw "Type name is not a typename: " + type_name;
	SymbolTable* object_symbol_table = new SymbolTable(this, object_name);
	// TODO: Add all the members of the class/family to the symbol table
	child_symbol_tables[object_name] = object_symbol_table;
}

/**
 * @brief Utility function to display the symbol table
 * Prints each symbol table with its namespace name, followed by its child symbol tables
 */
void SymbolTable::printSymbolTable(std::ostream& out_file, int indentation){
	for(int i = 0; i < indentation; i++)
		out_file << "\t";
	out_file << "Symbol Table: " << namespace_name << '\n';
	for(auto symbol : symbol_table){
		for(int i = 0; i < indentation; i++)
			out_file << "\t";
		out_file << symbol.second << '\n';
	}
	for(auto child_symbol_table : child_symbol_tables){
		child_symbol_table.second->printSymbolTable(out_file, indentation + 1);
	}
}