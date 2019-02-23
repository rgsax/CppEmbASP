#include <string>

namespace embasp {

#ifndef OUTPUT_H
#define OUTPUT_H

/* represents a generic output for a solver */
class Output
{
public:
    Output(const std::string &initial_output): output(initial_output) { }
	Output(const std::string &out, const std::string &err): output(out), errors(err) { }

    inline std::string getErrors() { return errors; }
    inline std::string getOutput() { return output; }

    virtual void parse() { }

    inline void setErrors(const std::string &err) { this->errors = err; }
    inline void setOutput(const std::string &output) { this->output = output; }

    virtual ~Output() { }

protected:
    /* Variable in which results are stored */
	std::string output = "";
	/* The errors thrown by the solver */
    std::string errors = "";
};

#endif // OUTPUT_H

};
