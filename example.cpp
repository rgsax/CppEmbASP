#include "platforms/desktop/DesktopHandler.hpp"
#include "specializations/dlv2.hpp"
#include <iostream>

using namespace std;
using namespace embasp;

class Example : public Object {
public:
	Example(): Object("embaspFunziona") {
		initObject();
	}

	void initObject(vector<string> predicateArguments) override {
		initObject();
	}

	string toString() {
		return "Example class";
	}

protected:
	void initObject() override { }
} ;

class ExitCode : public Object {
public:
	ExitCode(int code = 0): Object("exit_code"), code(code) { }

	void initObject(vector<string> args) override final {
		code = stoi(args[0]);

		initObject();
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
	void initObject() override final {
		addArgument<int>(0, &code);
	}

private:
	int code;

};

int main() {

    DesktopHandler handler(new DLV2DesktopService("./dlv2"));
	InputProgram *program = new ASPInputProgram();

	program->addFilesPath("prova");
	program->addObjectInput(new ExitCode(0));
	program->addProgram("exit_code(1).");
	handler.addProgram(program);

	ASPMapper::getInstance()->registerObjectType<Example>();

	Output *output = handler.startSync();
	AnswerSets *answerSets = dynamic_cast<AnswerSets*>(output);

	for(auto answerSet : answerSets->getAnswersets()) {
		for(auto atom : answerSet->getAtoms()) {
			const type_info *tInfo = atom.getObjectTypeInfo();
			if(tInfo != nullptr)
				if(tInfo->name() == typeid(Example).name())
					cout<<"Embasp funziona!\n";

				if(tInfo->name() == typeid(ExitCode).name()) {
					ExitCode ec;
					ec.initObject(atom.getPredicateArguments());
					cout<<ec.toString()<<"\n";
				}
		}
	}
}
