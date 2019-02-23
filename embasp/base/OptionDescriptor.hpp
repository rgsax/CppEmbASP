#include <string>

namespace embasp {

#ifndef OPTIONDESCRIPTOR_H
#define OPTIONDESCRIPTOR_H

/* Represents options for a generic ASP programs */
class OptionDescriptor
{
public:
    OptionDescriptor(const std::string &initial_option): options(initial_option) { }

    /*
	 * concatenate a new option in a string format to the current options
	 */
	void addOption(const std::string &option) {
		if (options == "")
			options = option;
		else
			options += separator + option;
    }

    /* after using this method the options variable will be empty */
	void clear() {
		options = "";
    }

    /*
	 * Returns values stored in options
	 */
	std::string getOptions() {
		return options;
    }

    /* get separator character */
	std::string getSeparator() {
		return separator;
    }

    void setOptions(const std::string &option) {
		options = option;
    }

    /* Set separator character with new separator */
	void setSeparator(const std::string &separator) {
		this->separator = separator;
    }

    bool operator==(const OptionDescriptor &o) {
        return separator == o.separator && options == o.options;
    }

    virtual ~OptionDescriptor() {}

protected:
    /* used as option separator */
	std::string separator = "";
	/* where options are stored */
    std::string options = "";
};

#endif // OPTIONDESCRIPTOR_H

};
