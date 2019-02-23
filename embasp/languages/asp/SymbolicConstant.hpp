#include <string>

namespace embasp {

#ifndef SYMBOLICCONSTANT_H
#define SYMBOLICCONSTANT_H

class SymbolicConstant
{
public:

	SymbolicConstant(): value("") {	}

	SymbolicConstant(const std::string &value): value(value) {	}

	std::string getValue() {
		return value;
	}

	void setValue(const std::string &value) {
		this->value = value;
	}

	std::string toString() {
		return value;
    }

    virtual ~SymbolicConstant() {}

private:
    std::string value;
};

#endif // SYMBOLICCONSTANT_H

};
