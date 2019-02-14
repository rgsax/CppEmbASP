#include "platforms/desktop/DesktopHandler.hpp"
#include "specializations/dlv2.hpp"
#include <iostream>

using namespace std;
using namespace embasp;

class Pesca : public Object {
public:
	Pesca(): Object("pesca") {
		initObject();
	}

	Pesca(int value): Object("pesca"), value(value) {
		initObject();
	}

	void initObject(vector<string> predicateArguments) override {
		value = stoi(predicateArguments[0]);

		initObject();
	}

	vector<string> listArguments() override {
		return vector<string> {
			to_string(getArgument<int>(0))
		};
	}

	string toString() {
		return "Pesca{" + to_string(value) + "}";
	}

protected:
	void initObject() override {
		addArgument<int>(0, &value);
	}

private:
	int value;
} ;

int main() {
	ASPMapper::getInstance()->registerObjectType<Pesca>();

    DesktopHandler handler(new DLV2DesktopService("./dlv2"));
	//InputProgram *program = new InputProgram("banana(X) | pesca(X):- pera(X). pera(1). :~ banana(X). [1@1, X] :~ banana(X). [1@2, X]");
	InputProgram *program = new ASPInputProgram();
	program->addFilesPath("file_dlv");
	program->addObjectInput(new Pesca(237));
	handler.addProgram(program);
	Output *output = handler.startSync();
	AnswerSets *answerSets = dynamic_cast<AnswerSets*>(output);

	for(auto answerSet : answerSets->getAnswersets()) {
		// for(ObjectInfo objInfo : answerSet->getAtoms()) {
		// 	const type_info *tInfo = objInfo.getObjectTypeInfo();
		// 	if(tInfo != nullptr && tInfo->name() == typeid(Pesca).name()) {
		// 		Pesca p;
		// 		p.initObject(objInfo.getPredicateArguments());
		// 		cout<<p.toString()<<"\n";
		// 	}
		// }

		for(string as : answerSet->getAnswerSet())
			cout<<as<<"\n";

		for(auto &[level, cost] : answerSet->getLevelWeight()) {
			cout<<cost<<"@"<<level<<" ";
		}
		cout<<"\n";
	}
}
