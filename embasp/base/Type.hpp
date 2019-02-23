#include "Predicate.hpp"

namespace embasp {

#ifndef EMBASP_TYPE_H
#define EMBASP_TYPE_H

class _Type {
public:
	virtual Predicate* newInstance() const {
		return nullptr;
	}
};

template<typename T>
class Type : public _Type{

public:
	Predicate* newInstance() const override {
		return new T();
	}
};

bool same_type(_Type *t1, _Type *t2) {
	return typeid(*t1) == typeid(*t2);
}

#endif

};