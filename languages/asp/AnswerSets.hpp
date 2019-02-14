#include <list>
#include <string>
#include "../../base/Output.hpp"

namespace embasp {

#ifndef ANSWERSETS_H
#define ANSWERSETS_H

class AnswerSet;

/* A collection of AnswerSet */
class AnswerSets : public Output
{
public:
    AnswerSets(const std::string &out): Output(out) { }

	AnswerSets(const std::string &out, const std::string &err): Output(out, err) { }

	std::list<AnswerSet*> getAnswersets() {
		if (answersets.empty()) {
			parse();
		}

		return answersets;
	}

	std::string getAnswerSetsString() {
		return output;
}

    virtual ~AnswerSets() {}

protected:
    std::list<AnswerSet*> answersets;
};

#endif // ANSWERSETS_H

};
