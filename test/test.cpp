#include <iostream>
#include "Object.hpp"
#include <typeinfo>

using namespace std;

namespace embasp {

class _Type {
public:
	virtual Object* newInstance() const {
		return nullptr;
	}
};

template<typename T>
class Type : public _Type{

public:
	Object* newInstance() const override {
		return new T();
	}
};

template<typename T>
const type_info Type<T>::_info = typeid(T);

bool same_type(_Type *t1, _Type *t2) {
	return typeid(*t1) == typeid(*t2);
}

class Oggetto1 : public Object {
public:
	Oggetto1(): Object("oggetto1") { }
	void initObject(std::vector<std::string> args) { }

protected:
	void initObject() { }
};

class Oggetto2 : public Object {
public:
	Oggetto2(): Object("oggetto2") { }
	void initObject(std::vector<std::string> args) { }

protected:
	void initObject() { }
};

};

using namespace embasp;

int main() {
	_Type *t1 = new Type<Oggetto1>;
	_Type *t2 = new Type<Oggetto1>;
	_Type *t3 = new Type<Oggetto2>;
	cout<<typeid(Type<int>).name()<<" | "<<typeid(Type<string>).name()<<"\n";

	cout<<boolalpha<<same_type(t1, t2)<<" and "<<same_type(t1, t3);
}
