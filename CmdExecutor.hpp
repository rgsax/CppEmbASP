#ifndef CMDEXECUTOR_H
#define CMDEXECUTOR_H

/*
 * Compile using the following flags: -std=c++17 -lstdc++fs
 */

#include <boost/filesystem.hpp> //C++17 and newer versions
#include <cstdlib>
#include <fstream>
#include <stdexcept>

class CmdExecutor {
public:
	static CmdExecutor* getInstance() {
		if(instance == nullptr)
			instance = new CmdExecutor();

		return instance;
	}

	int execute(std::string command) {
		command += " > " + output_path + " 2> " + error_output_path; //The output will be redirected to the temporary files
		int status = std::system(command.c_str());

		collectOutput();

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
	static CmdExecutor *instance;
	static const std::string OUTPUT_FILENAME;
	static const std::string ERROR_OUTPUT_FILENAME;

    std::istream *output_stream = nullptr;
    std::istream *error_output_stream = nullptr;

	std::string output_path;
	std::string error_output_path;


	void collectOutput() {
		delete output_stream; //Prevent memory leak
		delete error_output_stream;
		output_stream = new std::ifstream(output_path); //Open the temporary file containing the output of the command using a stream
        error_output_stream = new std::ifstream(error_output_path); //Open the temporary file containing the error output of the command using a stream
	}

	CmdExecutor() {
        std::string tmpDir = boost::filesystem::temp_directory_path().string();
		output_path = tmpDir + "/" + OUTPUT_FILENAME; //The temporary file for the output
        error_output_path = tmpDir + "/" + ERROR_OUTPUT_FILENAME;
	}

	CmdExecutor(const CmdExecutor &c) {	}

};

CmdExecutor* CmdExecutor::instance = nullptr;
const std::string CmdExecutor::OUTPUT_FILENAME = "cmd_executor_output";
const std::string CmdExecutor::ERROR_OUTPUT_FILENAME = "cmd_executor_error_output";

#endif
