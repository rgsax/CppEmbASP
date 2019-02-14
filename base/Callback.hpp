namespace embasp {

#ifndef CALLBACK_H
#define CALLBACK_H

class Output;

/*
 * This interface is used to communicate results of solver invocation to the user
 */
class Callback
{
public:
    virtual void callback(Output *o) = 0;
    virtual ~Callback() { }
};

#endif // CALLBACK_H

};
