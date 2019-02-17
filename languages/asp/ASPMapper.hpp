#include <exception>
#include "../../base/Type.hpp"

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

	template<typename T>
	void registerObjectType() {
		_Type *type = new Type<T>;
		Object *obj = type->newInstance();

		registeredTypes.insert_or_assign(obj->getName(), type);

		delete obj;
	}

	Object* getObject(std::string predicate) {
		std::string name = predicate.substr(0, predicate.find("("));

		_Type *type = nullptr;

		try{
			type = registeredTypes.at(name);
		} catch(const std::exception &e) {
			return nullptr;
		}

		std::string arguments = predicate.substr(predicate.find("(") + 1, predicate.length() - 1);
		std::vector<std::string> args;

		size_t pos = 0;
		std::string delimiter = ",";
		while((pos = arguments.find(delimiter)) != std::string::npos) {
			args.push_back(arguments.substr(0, pos));
			arguments.erase(0, pos + delimiter.length());
		}

		args.push_back(arguments);

		Object *obj = type->newInstance();
		obj->initObject(args);

		return obj;
	}

	std::unordered_map<std::string, _Type*> getRegisteredTypes() {
		return registeredTypes;
	}

	template<typename T>
	void unregisterObjectType() {
		_Type *type = new Type<T>;
		Object *obj = type->newInstance();

		registeredTypes.erase(obj->getName());

		delete obj;
		delete type;
	}

	template<typename T>
	bool isRegistered() {
		_Type *type = new Type<T>;
		Object *obj = type->newInstance();

		bool registered = registeredTypes.find(obj->getName()) != registeredTypes.end();

		delete obj;
		delete type;
		return registered;
	}

	std::string getString(Object *object) {
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
	std::unordered_map<std::string, _Type*> registeredTypes;
};

ASPMapper* ASPMapper::instance = nullptr;

#endif

};
