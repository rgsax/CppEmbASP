#ifndef CMDEXECUTOR_H
#define CMDEXECUTOR_H

/*
 * Compile using the following flags: -lboost_system
 */

#include <boost/process.hpp>
#include <memory>
#include <stdexcept>
#include <iostream>

namespace boost_process = boost::process;

class CmdExecutor {
public:
	static std::shared_ptr<CmdExecutor> getInstance() {
		if(instance == nullptr)
			instance = std::make_shared<CmdExecutor>();

		return instance;
	}

	int execute(const std::string &command) {
		boost_process::ipstream *out = new boost_process::ipstream;
		boost_process::ipstream *err = new boost_process::ipstream;

		int status = boost_process::system(command, boost_process::std_out > (*out), boost_process::std_err > (*err));

		delete output_stream;
		delete error_output_stream;

		output_stream = out;
		error_output_stream = err;

		return status;
	}

	std::istream* getOutputStream() {
        if(output_stream == nullptr)
            throw std::runtime_error("Missing execution before output stream request");

        return output_stream;
	}

	std::istream* getErrorOutputStream() {
        if(error_output_stream == nullptr)
            throw std::runtime_error("Missing execution before error output stream request");

        return error_output_stream;
	}

	~CmdExecutor() {
		delete output_stream;
		delete error_output_stream;
	}

private:
	static std::shared_ptr<CmdExecutor> instance;

    std::istream *output_stream = nullptr;
    std::istream *error_output_stream = nullptr;

};

std::shared_ptr<CmdExecutor> CmdExecutor::instance = std::shared_ptr<CmdExecutor>(nullptr);

#endif
