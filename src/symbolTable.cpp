#include "symbolTable.h"
#include <sstream>

extern void yyerror(const char* s);
typedef struct YYLTYPE
{
	int first_line;
	int first_column;
	int last_line;
	int last_column;
	const char *filename;
} YYLTYPE;

std::ostream& operator << (std::ostream& os, const YYLTYPE* loc){
	if(loc == NULL) return os << "Inbuilt language defined symbol";
	return os << "line " << loc->first_line << "-(" << loc->first_column << ".." << loc->last_column << ")";
}

std::ostream& operator << (std::ostream& os, const KIND& type){
	switch(type){
		case KIND::PRIMITIVE_VAR: return os << "Primitive variable";
		case KIND::OBJECT_VAR: return os << "Object variable";
		case KIND::FAMILY: return os << "Family typename";
		case KIND::FUNCTION: return os << "Function";
		case KIND::INBUILT_PRIMITIVE_TYPE: return os << "Inbuilt primitive typename";
		case KIND::INBUILT_FAMILY: return os << "Inbuilt family typename";
		case KIND::INBUILT_FUNCTION: return os << "Inbuilt function";
		case KIND::UNKNOWN: 
		default: return os << "Unknown";
	}
}

/**
 * @brief Overloading << to print a symbol
 * 
 * @param out 
 * @param symbol 
 * @return std::ostream& 
 */
std::ostream& operator << (std::ostream& out, const Symbol& symbol){
	return out << symbol.name << " : " << symbol.type_name << " (" << symbol.type << ") " << symbol.location;
	return out;
}

/// @brief Constructor and destructor for Symbol class
Symbol::Symbol(std::string name, KIND type, std::string type_name, YYLTYPE* location)
	:name(name), type(type), type_name(type_name), location(location) 
{
	if(location != NULL) 
		this->location = new YYLTYPE(*location);
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
	if(namespace_name == ""){
		namespace_name = parent->namespace_name + "::" + std::to_string(child_symbol_tables.size());
	}
	if(parent != NULL)
		parent->child_symbol_tables[namespace_name] = this;
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
	addSymbol("int", "int", NULL, KIND::INBUILT_PRIMITIVE_TYPE);
	addSymbol("float", "float", NULL, KIND::INBUILT_PRIMITIVE_TYPE);
	addSymbol("string", "string", NULL, KIND::INBUILT_PRIMITIVE_TYPE);
	addSymbol("bool", "bool", NULL, KIND::INBUILT_PRIMITIVE_TYPE);
	addSymbol("void", "void", NULL, KIND::INBUILT_PRIMITIVE_TYPE);
}

/**
 * @brief Add the inbuilt family typenames such as Point, Path, Image, Rectangle, Circle, Ellipse, Polygon, Curve, Color
 * 
 */
void SymbolTable::addInbuiltFamilyTypenames(){
	addSymbol("Point", "Point", NULL, KIND::INBUILT_FAMILY);
	addSymbol("Path", "Path", NULL, KIND::INBUILT_FAMILY);
	addSymbol("Image", "Image", NULL, KIND::INBUILT_FAMILY);
	addSymbol("Rectangle", "Rectangle", NULL, KIND::INBUILT_FAMILY);
	addSymbol("Circle", "Circle", NULL, KIND::INBUILT_FAMILY);
	addSymbol("Ellipse", "Ellipse", NULL, KIND::INBUILT_FAMILY);
	addSymbol("Polygon", "Polygon", NULL, KIND::INBUILT_FAMILY);
	addSymbol("Curve", "Curve", NULL, KIND::INBUILT_FAMILY);
	addSymbol("Color", "Color", NULL, KIND::INBUILT_FAMILY);

	// TODO: Create a new symbol table for each of the family types and add the inbuilt functions and constants
}

/**
 * @brief Add the inbuilt functions such as print, draw, etc. 
 * 
 */
void SymbolTable::addInbuiltFunctions(){
	addSymbol("print", "void", NULL, KIND::INBUILT_FUNCTION);
	addSymbol("draw", "void", NULL, KIND::INBUILT_FUNCTION);
}

/**
 * @brief Add the inbuilt constants such as Pi, etc. 
 * 
 */
void SymbolTable::addInbuiltConstants(){
	// addSymbol("Pi", "float", NULL, KIND::PRIMITIVE_VAR);
}


SymbolTable* SymbolTable::addPrimitiveVariable(std::string identifier_name, std::string type_name, YYLTYPE* location){
	symbol_table[identifier_name] = Symbol(identifier_name, KIND::PRIMITIVE_VAR, type_name, location);
	return this;
}

SymbolTable* SymbolTable::addObjectVariable(std::string identifier_name, std::string type_name, YYLTYPE* location){
	symbol_table[identifier_name] = Symbol(identifier_name, KIND::OBJECT_VAR, type_name, location);
	// TODO: Create a data entry for the object variable
	return this;
}

SymbolTable* SymbolTable::addFunction(std::string identifier_name, std::string type_name, YYLTYPE* location){
	symbol_table[identifier_name] = Symbol(identifier_name, KIND::FUNCTION, type_name, location);
	SymbolTable* functionSymbolTable = new SymbolTable(this, identifier_name);

	return functionSymbolTable;
}

SymbolTable* SymbolTable::addFamily(std::string identifier_name, YYLTYPE* location){
	symbol_table[identifier_name] = Symbol(identifier_name, KIND::FAMILY, identifier_name, location);
	SymbolTable* familySymbolTable = new SymbolTable(this, identifier_name);

	return familySymbolTable;
}

/**
 * @brief Adds a new symbol to the symbol table when it is declared
 * 
 * @param identifier_name 
 * @param type_name 
 * @param location 
 * @param type 
 * 
 * @return The current symbol table 
 */
SymbolTable* SymbolTable::addSymbol(std::string identifier_name, std::string type_name, YYLTYPE* location, KIND type){
	if(location != NULL)
		std::cerr << "Adding symbol: " << identifier_name << " of type: " << type_name << " at location: " << location << " in namespace " << namespace_name << std::endl;
	if(type == KIND::UNKNOWN){
		Symbol* type_name_symbol = lookUp(type_name);
		if(type_name_symbol == NULL)
			yyerror(std::string("Error: Type name not found: " + type_name).c_str());
		else switch(type_name_symbol->getType()){
			case KIND::INBUILT_PRIMITIVE_TYPE: 
				type = KIND::PRIMITIVE_VAR; break;
			case KIND::INBUILT_FAMILY:
			case KIND::FAMILY:
				type = KIND::OBJECT_VAR; break;
			default: 
				yyerror(std::string("Error: Type name not found: " + type_name).c_str());
		}
	}

	if(lookUp(identifier_name) != NULL){
		std::stringstream error;
		error << "Error: Redeclaration of identifier \"" << identifier_name << "\". First defined at " << lookUp(identifier_name)->getLocation() << std::endl;
		yyerror(error.str().c_str());
	}

	switch(type){
		case KIND::PRIMITIVE_VAR: return addPrimitiveVariable(identifier_name, type_name, location);
		case KIND::OBJECT_VAR: return addObjectVariable(identifier_name, type_name, location);
		case KIND::FUNCTION: return addFunction(identifier_name, type_name, location);
		case KIND::FAMILY: return addFamily(identifier_name, location);
		case KIND::INBUILT_PRIMITIVE_TYPE: 
		case KIND::INBUILT_FAMILY:
		case KIND::INBUILT_FUNCTION: symbol_table[identifier_name] = Symbol(identifier_name, type, type_name, location); return this;
		default:
			yyerror(std::string("Error: Unknown type: " + type_name).c_str());
	}
	// TODO: Create new symbol table for functions

	return this;
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
 * @brief Utility function to display the symbol table
 * Prints each symbol table with its namespace name, followed by its child symbol tables
 */
void SymbolTable::printSymbolTable(std::ostream& out_file, int indentation){
	for(int i = 0; i < indentation; i++)
		out_file << "\t";
	out_file << "\nSymbol Table: " << namespace_name << '\n';
	for(auto& [name, symbol] : symbol_table){
		if(symbol.getType() == KIND::INBUILT_FUNCTION || symbol.getType() == KIND::INBUILT_FAMILY || symbol.getType() == KIND::INBUILT_PRIMITIVE_TYPE)
			continue;
		for(int i = 0; i < indentation; i++)
			out_file << "\t";
		out_file << symbol << '\n';
	}
	for(auto child_symbol_table : child_symbol_tables){
		child_symbol_table.second->printSymbolTable(out_file, indentation + 1);
	}
}