#ifndef EXAMPLES_HPP
#define EXAMPLES_HPP

#include "base/Predicate.hpp"

using std::string;
using std::stoi;
using std::to_string;
using std::vector;

class Example : public embasp::Predicate {
public:
	Example(): Predicate("embaspFunziona") {
		initPredicate();
	}

	void initPredicate(const vector<string> &predicateArguments) override {
		initPredicate();
	}

	string toString() {
		return "Example class";
	}

protected:
	void initPredicate() override { }
};

class ExitCode : public embasp::Predicate {
public:
	ExitCode(int code = 0): Predicate("exit_code"), code(code) { }

	void initPredicate(const vector<string> &args) override final {
		code = stoi(args[0]);

		initPredicate();
	}

	vector<string> listArguments() override {
		return vector<string> {
			to_string(code)
		};
	}

	string toString() {
		return "ExitCode{" + to_string(code) + "}";
	}

protected:
	void initPredicate() override final {
		addArgument<int>(0, &code);
	}

private:
	int code;

};

#endif
