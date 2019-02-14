#include <list>

namespace embasp {

#ifndef SERVICE_H
#define SERVICE_H

class Callback;
class InputProgram;
class OptionDescriptor;
class Output;

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
