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
    virtual void startAsync(Callback *callback, const std::list<InputProgram*> &programs, const std::list<OptionDescriptor*> &options) = 0;

    /*
	 * Starts ASP solving Syncronously on a subset of data and options.
	 */
    virtual OutputSharedPtr startSync(const std::list<InputProgram*> &programs, const std::list<OptionDescriptor*> &options) = 0;

    virtual ~Service() {}
};

#endif // SERVICE_H

};
