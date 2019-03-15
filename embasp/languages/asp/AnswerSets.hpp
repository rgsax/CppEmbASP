#include <list>
#include <string>
#include "../../base/Output.hpp"
#include "AnswerSet.hpp"

namespace embasp {

#ifndef ANSWERSETS_H
#define ANSWERSETS_H

/* A collection of AnswerSet */
class AnswerSets : public Output
{
public:
    AnswerSets(const std::string &out): Output(out) { }

	AnswerSets(const std::string &out, const std::string &err): Output(out, err) { }

	std::list<AnswerSetSharedPtr> getAnswersets() {
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
    std::list<AnswerSetSharedPtr> answersets;
};

#endif // ANSWERSETS_H

};
