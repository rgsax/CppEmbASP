#include "../../platforms/desktop/DesktopService.hpp"
#include "../../base/OptionDescriptor.hpp"
#include "../DLV2AnswerSets.hpp"

namespace embasp {

#ifndef DLV2DESKTOPSERVICE_H
#define DLV2DESKTOPSERVICE_H

class DLV2DesktopService : public DesktopService
{
public:
    DLV2DesktopService(const std::string &exe_path): DesktopService(exe_path) {
        load_from_STDIN_option = "--stdin";
    }

    void startAsync(Callback *callback, std::list<InputProgram*> programs, std::list<OptionDescriptor*> options) override{
		options.push_back(competitionOutput);
		DesktopService::startAsync(callback, programs, options);
    }

    Output* startSync(std::list<InputProgram*> programs, std::list<OptionDescriptor*> options) override{
		options.push_back(competitionOutput);
		return DesktopService::startSync(programs, options);
    }

    virtual ~DLV2DesktopService() {
        delete competitionOutput;
    }

protected:
    Output* getOutput(std::string output, std::string error) override{
		if(!error.empty())
			std::cerr<<"Some error occured during execution\n";
		return new DLV2AnswerSets(output, error);
}

private:
    OptionDescriptor *competitionOutput = new OptionDescriptor("--competition-output");
};

#endif // DLV2DESKTOPSERVICE_H

};
