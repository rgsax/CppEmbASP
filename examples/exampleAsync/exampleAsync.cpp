#include "../../embasp/platforms/desktop/DesktopHandler.hpp"
#include "../../embasp/specializations/dlv2.hpp"
#include "../example_classes.hpp"
#include <iostream>

using namespace std;
using namespace embasp;

class MyASPCallback : public Callback {
public:
	void callback(OutputSharedPtr output) const override {
		auto answerSets = dynamic_cast<AnswerSets*>(output.get());

		for(auto answerSet : answerSets->getAnswersets()) {
			for(auto atom : answerSet->getAtoms()) {
				if(atom != nullptr) {
					if(typeid(*atom) == typeid(Example))
						cout<<"embasp funziona!!\n";
					else if(typeid(*atom) == typeid(ExitCode))
						cout<<dynamic_cast<ExitCode*>(atom.get())->toString()<<"\n";
				}
			}
		}
	}

};


int main() {
	DesktopService *desktopService = new DLV2DesktopService("../dlv2");
    DesktopHandler handler(desktopService);
	InputProgram *program = new ASPInputProgram();

	program->addFilesPath("../prova");
	ExitCode *code = new ExitCode(0);
	program->addPredicateInput(code);
	program->addProgram("exit_code(1).");
	handler.addProgram(program);

	auto mapper = ASPMapper::getInstance();

	mapper->registerPredicateType<Example>();
	mapper->registerPredicateType<ExitCode>();

	Callback *myASPCallback = new MyASPCallback();

	handler.startAsync(myASPCallback);

	delete code;
	delete myASPCallback;
	delete program;
	delete desktopService;
}
