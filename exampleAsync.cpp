#include "platforms/desktop/DesktopHandler.hpp"
#include "specializations/dlv2.hpp"
#include "example_classes.hpp"
#include <iostream>

using namespace std;
using namespace embasp;

class MyASPCallback : public Callback {
public:
	void callback(Output *output) const override {
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

};


int main() {

    DesktopHandler handler(new DLV2DesktopService("./dlv2"));
	InputProgram *program = new ASPInputProgram();

	program->addFilesPath("prova");
	program->addPredicateInput(new ExitCode(0));
	program->addProgram("exit_code(1).");
	handler.addProgram(program);

	ASPMapper *mapper = ASPMapper::getInstance();

	mapper->registerPredicateType<Example>();
	mapper->registerPredicateType<ExitCode>();

	Callback *myASPCallback = new MyASPCallback();

	handler.startAsync(myASPCallback);

	delete myASPCallback;
}
