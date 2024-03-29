#include "DesktopService.hpp"
#include "../../base/Handler.hpp"

namespace embasp {

#ifndef DESKTOPHANDLER_H
#define DESKTOPHANDLER_H

/*
 * is a specialization for a Desktop platform
 */
class DesktopHandler : public Handler
{
public:
    DesktopHandler(DesktopService *service): service(service) { }

    void startAsync(Callback *c, const std::list<int> &program_index, const std::list<int> &option_index) override{
        std::list<InputProgram*> input_programs = collect_programs(program_index);
        std::list<OptionDescriptor*> input_options = collect_options(option_index);

        service->startAsync(c, input_programs, input_options);
    }

	void startAsync(Callback *c) override {
		startAsync(c, std::list<int>(), std::list<int>());
	}

	OutputSharedPtr startSync() override {
		return Handler::startSync();
	}

    OutputSharedPtr startSync(const std::list<int> &program_index, const std::list<int> &option_index) override{
		std::list<InputProgram*> input_programs = collect_programs(program_index);
		std::list<OptionDescriptor*> input_options = collect_options(option_index);

		return service->startSync(input_programs, input_options);
    }

    virtual ~DesktopHandler() { }

private:
    DesktopService *service = nullptr;
};

#endif // DESKTOPHANDLER_H

};
