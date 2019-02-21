#include <list>
#include <unordered_map>
#include <string>

#include "ASPMapper.hpp"

namespace embasp {

#ifndef ANSWERSET_H
#define ANSWERSET_H

/*
 * A collection of data representing a generic Answer Set
 */
class AnswerSet
{
public:
    AnswerSet() {}

    AnswerSet(const std::list<std::string> &output) {
		value = output;
	}

	AnswerSet(const std::list<std::string> &value, const std::unordered_map<int, int> &weightMap) {
		this->value = value;
		weight_map = weightMap;
    }

    /*
	 * Return the current value data
	 */
	std::list<std::string> getAnswerSet() {
		return value;
	}

	/*
	 * Return atoms stored in atoms
	 */
	std::list<Predicate*> getAtoms() {
		if (atoms.empty()) {
			ASPMapper *mapper = ASPMapper::getInstance();
			for (const std::string &atom : value) {
				Predicate *obj = mapper->getPredicate(atom);

				atoms.push_back(obj);
			}
		}

		return atoms;
	}

	std::unordered_map<int, int> getLevelWeight() {
		return weight_map;
	}

	std::unordered_map<int, int> getWeights() {
		return weight_map;
	}

	std::string toString() {
        std::string out = "";

        for(const std::string &s : value)
            out += " " + s;

		return out;
    }

    virtual ~AnswerSet() {}

private:
    /* where data of answer set is stored */
	std::list<std::string> value;
	/* where weights of the answer set are stored */
	std::unordered_map<int, int> weight_map;
	/* where Answer set's atoms are stored */
    std::list<Predicate*> atoms;
};

#endif // ANSWERSET_H

};
