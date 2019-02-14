#include <unordered_map>
#include <list>
#include "InputProgram.hpp"
#include "OptionDescriptor.hpp"

namespace embasp {

#ifndef HANDLER_H
#define HANDLER_H

/*
 * A collection of InputProgram and OptionDescriptor.
 * The subclasses have to implement startAsync(Callback*, list, list)and startSync(list, list) methods.
 * Each instance inside programs and options are represented by an integer (id) , respectively.
 */
class Handler
{
public:

    /*
	 * Add a new element inside {@link #options} set.
	 */
    int addOption(OptionDescriptor *o) {
		int last_index = options.size();
		int current_value = last_index;
		options.insert_or_assign(last_index++, o); //C++17 or newer versions
		return current_value;
    }

    /*
	 * Add a new element inside programs set.
	 */
    int addProgram(InputProgram *program) {
		int last_index = programs.size();
		int current_value = last_index;
		programs.insert_or_assign(last_index++, program); //C++17 or newer versions
		return current_value;
    }

    /*
	 * Returns the specified InputProgram element
	 */
    InputProgram* getInputProgram(int key) {
            return programs.at(key);
    }

    /*
	 * Returns the specified {@link OptionDescriptor} element
	 */
    OptionDescriptor* getOptionDescriptor(int key) {
            return options.at(key);
    }

    /* Removes all of the elements from programs and options. Both of the collections will be empty after this method returns */
	void removeAll() {
		programs.clear();
		options.clear();
    }

    /*
	 * Removes the element associate within the given id from options set.
	 */
    void removeOption(int option_id) {
		options.erase(option_id);
    }

    /*
	 * Removes every occurrence of a specified OptionDescriptor element from options set.
	 */
    bool removeOption(OptionDescriptor *o) {
		bool result = false;
		for (const auto &entry : options)
			if (*(entry.second) == *o) {
				options.erase(entry.first);
				result = true;
			}

		return result;
    }

    /*
	 * Removes every occurrence of a specified InputProgram element from programs set.
	 */
    bool removeProgram(InputProgram *p) {
		bool result = false;
		for (const auto &entry : programs)
			if (*(entry.second) == *p) {
				programs.erase(entry.first);
				result = true;
			}
		return result;
    }

    /*
	 * Removes the element associate within the given id from programs set.
	 */
    void removeProgram(int program_id) {
		programs.erase(program_id);
    }

    void startAsync(Callback *c) {
		startAsync(c, std::list<int>(), std::list<int>());
    }

    /*
	 * This method have to be implemented by subclasses to execute solver in a asynchronous way, if no parameters are given
	 * the entire sets of programs and option are used
	 */
	virtual void startAsync(Callback *c, std::list<int> program_index, std::list<int> option_index) { }

	Output* startSync() {
		return startSync(std::list<int>(), std::list<int>());
    }

    /**
	 * This method have to be implemented by subclasses to execute solver in a synchronous way, if no parameters are given
	 * the entire sets of programs and option are used
	 */
	virtual Output* startSync(std::list<int> program_index, std::list<int> option_index) {
		return nullptr;
    }

    virtual ~Handler() { }

protected:
    std::unordered_map<int, InputProgram*> programs;
    std::unordered_map<int, OptionDescriptor*> options;

    std::list<OptionDescriptor*> collect_options(const std::list<int> &option_index) {
		std::list<OptionDescriptor*> input_option;

		if (option_index.empty())
			for (const auto &option : options)
				input_option.push_back(option.second);
		else
			for (int index : option_index)
				input_option.push_back(options.at(index));
		return input_option;
    }

    std::list<InputProgram*> collect_programs(const std::list<int> &program_index) {
		std::list<InputProgram*> input_programs;

		if (program_index.empty())
			for (const auto &program : programs)
				input_programs.push_back(program.second);
		else
			for (int index : program_index)
				input_programs.push_back(programs.at(index));
		return input_programs;
    }
};

#endif // HANDLER_H

};
