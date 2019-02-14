#include <exception>
#include "../../base/Object.hpp"
#include "../../base/ObjectInfo.hpp"

namespace embasp {

#ifndef ASPMAPPER_H
#define ASPMAPPER_H

class ASPMapper {
public:

	static ASPMapper* getInstance() {
		if(instance == nullptr) {
			instance = new ASPMapper();
		}

		return instance;
	}

	void registerObjectType(Object *object) {
		registeredTypes.insert_or_assign(object->getName(), &typeid(*object));
	}

	template<typename T>
	void registerObjectType() {
		T *tmp = new T();
		registerObjectType(tmp);
		delete tmp;
	}

	ObjectInfo getObjectDescription(std::string predicate) {
		std::string name = predicate.substr(0, predicate.find("("));

		const std::type_info *tInfo = nullptr;

		try{
			tInfo = registeredTypes.at(name);
		} catch(const std::exception &e) { }

		std::string arguments = predicate.substr(predicate.find("(") + 1, predicate.length() - 1);
		std::vector<std::string> args;

		size_t pos = 0;
		std::string delimiter = ",";
		while((pos = arguments.find(delimiter)) != std::string::npos) {
			args.push_back(arguments.substr(0, pos));
			arguments.erase(0, pos + delimiter.length());
		}

		args.push_back(arguments);

		return ObjectInfo(tInfo, args);
	}

	std::unordered_map<std::string, const std::type_info*> getRegisteredTypes() {
		return registeredTypes;
	}

	void unregisterObjectType(Object *object) {
		registeredTypes.erase(object->getName());
	}

	bool isRegistered(Object *object) {
		return registeredTypes.find(object->getName()) != registeredTypes.end();
	}

	std::string getString(Object *object) {
		if(!isRegistered(object))
			registerObjectType(object);

		std::string objString = object->getName();

		std::vector<std::string> argumentList = object->listArguments();
		if(!argumentList.empty()) {
			objString += '(';
			for(const auto &arg : argumentList) {
				objString += arg + ',';
			}

			size_t lastPos = objString.length() - 1;
			if(objString[lastPos] == ',')
				objString[lastPos] = ')';
			else
				objString += ')';
		}

		return objString;
	}

private:
	static ASPMapper *instance;
	std::unordered_map<std::string, const std::type_info*> registeredTypes;

};

ASPMapper* ASPMapper::instance = nullptr;

#endif

};
