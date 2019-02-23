#include "../../base/OptionDescriptor.hpp"

namespace embasp {

#ifndef ASPFILTEROPTION_H
#define ASPFILTEROPTION_H

/* Generic filter option for ASP solver */

class ASPFilterOption : public OptionDescriptor
{
    public:
        ASPFilterOption(): OptionDescriptor("-filter=") { }
};

#endif // ASPFILTEROPTION_H

};
