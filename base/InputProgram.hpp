#include <list>
#include <string>
#include "Predicate.hpp"

namespace embasp {

#ifndef INPUTPROGRAM_H
#define INPUTPROGRAM_H

/* Represents a generic option */
class InputProgram
{
public:
    /* Creates a new programs , setting space as default separator */
	InputProgram() {
		separator = " ";
    }

    /*
	 * instantiate a new InputProgram
	 */
   InputProgram(Predicate *inputObj) {
		addPredicateInput(inputObj);
   }

    InputProgram(const std::string &initial_program) {
            programs = initial_program;
    }

    /*
	 * add a new file path into {@link #files_paths}
	 */
	void addFilesPath(const std::string &file_path) {
		files_paths.push_back(file_path);
    }

	virtual void addPredicateInput(Predicate *inputObj) {	}

	void addPredicatesInput(const std::list<Predicate*> &inputObjs) {
		for (Predicate *inputObj : inputObjs)
			addPredicateInput(inputObj);
	}

    /*
	 * Adds a new instruction directly into programs
	 */
	void addProgram(const std::string &new_instruction) {
		if (programs == "")
			programs = new_instruction;
		else
			programs += separator + new_instruction;
    }

	/* After this method both files_path and programs will be empty */
	void clearAll() {
		clearFilesPaths();
		clearPrograms();
    }

    /* After this method files_paths will be empty */
	void clearFilesPaths() {
		files_paths.clear();
    }

    /* After this method programs will be empty */
	void clearPrograms() {
		programs = "";
    }

    std::list<std::string> getFilesPaths() {
		return files_paths;
    }

    /** Returns data stored in programs */
    std::string getPrograms() {
        return programs;
    }

    /*
	 * get separator character
     */
	std::string getSeparator() {
		return separator;
    }

    /*
	 * Returns files paths for this programs
	 */
	std::string getStringOfFilesPaths() {
        std::string to_return = "";
		for (std::string paths : files_paths)
			if (paths.length() != 0)
				to_return += paths + " ";

		return to_return;
    }

    /*
	 * sets programs value to the new given one
	 */
	void setPrograms(const std::string &programs) {
		this->programs = programs;
    }

    /*
	 * Set programs separator to current value
	 */
	void setSeparator(const std::string &separator) {
		this->separator = separator;
    }

    bool operator==(const InputProgram &p) {
        return separator == p.separator && programs == p.programs;
    }

    virtual ~InputProgram() {}

protected:
    /* where programs data is stored */
	std::string programs = "";

	/* used as separator for programs */
    std::string separator = "";

private:
    /* where associated files are stored */
    std::list<std::string> files_paths;
};

#endif // INPUTPROGRAM_H

}
