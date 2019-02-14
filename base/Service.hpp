#include <list>
#include "Callback.hpp"
#include "InputProgram.hpp"
#include "OptionDescriptor.hpp"
#include "Output.hpp"

namespace embasp {

#ifndef SERVICE_H
#define SERVICE_H

class Service
{
public:
    /*
	 * Starts ASP solving Asyncronously on a subset of data and options.
	 */
    virtual void startAsync(Callback *callback, std::list<InputProgram*> programs, std::list<OptionDescriptor*> options) = 0;

    /*
	 * Starts ASP solving Syncronously on a subset of data and options.
	 */
    virtual Output* startSync(std::list<InputProgram*> programs, std::list<OptionDescriptor*> options) = 0;

    virtual ~Service() {}
};

#endif // SERVICE_H

};
