#include <any>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace embasp {

#ifndef EMBASP_PREDICATE_H
#define EMBASP_PREDICATE_H

class Predicate {
public:
	Predicate(const std::string &name): name(name) { }

	inline std::string getName() { return name; }

	template<typename T>
	T getArgument(int pos) {
		return *std::any_cast<T*>(arguments.at(pos));
	}

	virtual void initPredicate(const std::vector<std::string> &predicateArguments) = 0;

	virtual std::vector<std::string> listArguments() = 0;

	virtual ~Predicate() { }

protected:
	template<typename T>
	void addArgument(int pos, T *argument) {
		arguments.insert_or_assign(pos, std::make_any<T*>(argument));
	}

	virtual void initPredicate() = 0;

private:
	std::unordered_map<int, std::any> arguments;
	std::string name;
};

class Fact : public Predicate {
public:
	Fact(const std::string &name): Predicate(name) { }

	void initPredicate(const std::vector<std::string> &predicateArguments) override final {	}

	std::vector<std::string> listArguments() override final { return std::vector<std::string>(); }

protected:
	void initPredicate() override final { }
};

typedef std::shared_ptr<Predicate> PredicateSharedPtr;

#endif

};
