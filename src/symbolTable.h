#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <map>

enum class SYMBOL_TYPE{
	PRIMITIVE,
	OBJECT,
	TYPENAME,
	FUNCTION,
	UNKNOWN
};

/**
 * @brief Symbol table entry
 */
class Symbol{
private:
	std::string name;
	SYMBOL_TYPE type;
	std::string type_name;
	void* value;
	YYLTYPE location;
	// Properties

public:
	Symbol();
	Symbol(std::string name, SYMBOL_TYPE type = SYMBOL_TYPE::UNKNOWN): name(name), type(type) {}
	
	std::string getName() { return name; }
	SYMBOL_TYPE getType() { return type; }
	std::string getTypeName() { return type_name; }
	void* getValue() { return value; }
	YYLTYPE getLocation() { return location; }

	void setValue();

	friend std::ostream operator << (std::ostream& out, const Symbol& symbol);
};