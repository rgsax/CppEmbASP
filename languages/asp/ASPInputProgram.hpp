#include <string>
#include "../../base/InputProgram.hpp"
#include "../../base/Predicate.hpp"

namespace embasp {

#ifndef ASPINPUTPROGRAM_H
#define ASPINPUTPROGRAM_H

/* a generic ASP program , with the capabilities of retrieve data by predicates */
class ASPInputProgram : public InputProgram
{
public:

    ASPInputProgram(): InputProgram() {	}

	ASPInputProgram(Predicate *inputObj): InputProgram(inputObj) {	}

	ASPInputProgram(const std::string &initial_program): InputProgram(initial_program) { }

    /**
	 * transforms a given Predicate class into a InputProgram and adds it to the current programs
	 */
	void addPredicateInput(Predicate *inputObj) override {
		addProgram(ASPMapper::getInstance()->getString(inputObj) + ".");
	}

};

#endif // ASPINPUTPROGRAM_H

};
