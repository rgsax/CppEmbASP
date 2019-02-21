#include "platforms/desktop/DesktopHandler.hpp"
#include "specializations/dlv2.hpp"
#include <iostream>

using namespace std;
using namespace embasp;

class Example : public Predicate {
public:
	Example(): Predicate("embaspFunziona") {
		initPredicate();
	}

	void initPredicate(vector<string> predicateArguments) override {
		initPredicate();
	}

	string toString() {
		return "Example class";
	}

protected:
	void initPredicate() override { }
} ;

class ExitCode : public Predicate {
public:
	ExitCode(int code = 0): Predicate("exit_code"), code(code) { }

	void initPredicate(vector<string> args) override final {
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

int main() {

    DesktopHandler handler(new DLV2DesktopService("./dlv2"));
	InputProgram *program = new ASPInputProgram();

	program->addFilesPath("prova");
	program->addPredicateInput(new ExitCode(0));
	program->addProgram("exit_code(1).");
	handler.addProgram(program);

	ASPMapper::getInstance()->registerPredicateType<Example>();
	ASPMapper::getInstance()->registerPredicateType<ExitCode>();

	Output *output = handler.startSync();
	AnswerSets *answerSets = dynamic_cast<AnswerSets*>(output);

	for(auto answerSet : answerSets->getAnswersets()) {
		for(auto atom : answerSet->getAtoms()) {
			if(atom != nullptr) {
				if(typeid(*atom) == typeid(Example))
					cout<<"embasp funziona!!\n";
				else if(typeid(*atom) == typeid(ExitCode))
					cout<<dynamic_cast<ExitCode*>(atom)->toString()<<"\n";
			}
		}
	}
}
