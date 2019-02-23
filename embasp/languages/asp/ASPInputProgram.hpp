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

	ASPInputProgram(Predicate *inputPred): InputProgram(inputPred) {	}

	ASPInputProgram(const std::string &initial_program): InputProgram(initial_program) { }

    /**
	 * transforms a given Predicate class into a InputProgram and adds it to the current programs
	 */
	void addPredicateInput(Predicate *inputPred) override {
		addProgram(ASPMapper::getInstance()->getString(inputPred) + ".");
	}

};

#endif // ASPINPUTPROGRAM_H

};
