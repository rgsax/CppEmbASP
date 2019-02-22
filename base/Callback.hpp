#include "Output.hpp"

namespace embasp {

#ifndef CALLBACK_H
#define CALLBACK_H

/*
 * This interface is used to communicate results of solver invocation to the user
 */
class Callback
{
public:
    virtual void callback(Output *o) const = 0;
    virtual ~Callback() { }
};

#endif // CALLBACK_H

};
