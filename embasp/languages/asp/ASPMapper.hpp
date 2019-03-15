#include <exception>
#include <memory>
#include "../../base/Type.hpp"

namespace embasp {

#ifndef ASPMAPPER_H
#define ASPMAPPER_H

class ASPMapper {
public:

	static std::shared_ptr<ASPMapper> getInstance() {
		if(instance == nullptr) {
			instance = std::make_shared<ASPMapper>();
		}

		return instance;
	}

	template<typename T>
	void registerPredicateType() {
		std::shared_ptr<_Type> type = std::make_shared<Type<T>>();
		PredicateSharedPtr obj = type->newInstance();

		registeredTypes.insert_or_assign(obj->getName(), type);
	}

	PredicateSharedPtr getPredicate(const std::string &predicate) {
		std::string name = predicate.substr(0, predicate.find("("));

		std::shared_ptr<_Type> type = nullptr;

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

		PredicateSharedPtr obj = type->newInstance();
		obj->initPredicate(args);

		return obj;
	}

	std::unordered_map<std::string, std::shared_ptr<_Type>> getRegisteredTypes() {
		return registeredTypes;
	}

	template<typename T>
	void unregisterPredicateType() {
		std::shared_ptr<_Type> type = std::make_shared<Type<T>>();
		PredicateSharedPtr obj = type->newInstance();

		registeredTypes.erase(obj->getName());
	}

	template<typename T>
	bool isRegistered() {
		std::shared_ptr<_Type> type = std::make_shared<Type<T>>();
		PredicateSharedPtr obj = type->newInstance();

		bool registered = registeredTypes.find(obj->getName()) != registeredTypes.end();

		return registered;
	}

	std::string getString(Predicate *predicate) {
		std::string objString = predicate->getName();

		std::vector<std::string> argumentList = predicate->listArguments();
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
	static std::shared_ptr<ASPMapper> instance;
	std::unordered_map<std::string, std::shared_ptr<_Type>> registeredTypes;
};

std::shared_ptr<ASPMapper> ASPMapper::instance = std::shared_ptr<ASPMapper>(nullptr);

#endif

};
