#include <string>
#include <typeinfo>
#include <utility>
#include <vector>

namespace embasp {

#ifndef EMBASP_OBJECTINFO_H
#define EMBASP_OBJECTINFO_H

class ObjectInfo : private std::pair<const std::type_info*, std::vector<std::string>> {
public:
	ObjectInfo(const std::type_info *tInfo,
		const std::vector<std::string> &predicateArguments):
		std::pair<const std::type_info*, std::vector<std::string>>(std::make_pair(tInfo, predicateArguments)) { }

	const std::type_info* getObjectTypeInfo() const {
		return first;
	}

	std::vector<std::string> getPredicateArguments() const {
		return second;
	}
};

#endif

}
