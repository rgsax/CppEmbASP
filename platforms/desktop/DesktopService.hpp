#include <string>
#include <thread>
#include <iostream>
#include <typeinfo>
#include <sstream>
#include <boost/filesystem.hpp>
#include "../../base/Service.hpp"
#include "../../CmdExecutor.hpp"

namespace embasp {

#ifndef DESKTOPSERVICE_H
#define DESKTOPSERVICE_H

/**
 * is a specialization for a Desktop platform
 */
class DesktopService : public Service
{
public:
    DesktopService(const std::string &exe_path): exe_path(exe_path) { }

	std::string getExePath() {
		return exe_path;
	}

	/**
	 * set exe_path to a new path
	 */
	void setExePath(const std::string &exe_path) {
		this->exe_path = exe_path;
    }


	/**
	 * Start a new process for the exe_path and starts solving
	 */
	void startAsync(Callback *callback, std::list<InputProgram*> programs, std::list<OptionDescriptor*> options) override{

        std::thread(
            [&]{ callback->callback(startSync(programs, options)); }
        ).join();
    }

    /**
	 * Start a new process for the {@link #exe_path} and starts solving
	 */
	Output* startSync(std::list<InputProgram*> programs, std::list<OptionDescriptor*> options) override{
		std::string option;

		for (OptionDescriptor *o : options)
			if (o != nullptr) {
				option += o->getOptions();
				option += o->getSeparator();
			} else
				std::cerr<<"Warning : wrong "<<typeid(*o).name()<<"\n";

		std::string files_paths;
		std::string final_program;

		for (InputProgram *p : programs)
			if (p != nullptr) {
				final_program += p->getPrograms();
				for(std::string program_file: p->getFilesPaths()){
					if(boost::filesystem::exists(program_file) && !boost::filesystem::is_directory(program_file)) {
						files_paths += program_file;
						files_paths += " ";
					}
					else
						std::cerr<<"Warning : the file "<<boost::filesystem::absolute(program_file)<<" does not exists.\n";
				}
			} else
				std::cerr<<"Warning : wrong "<<typeid(*p).name()<<"\n";

		std::stringstream solverOutput;
		std::stringstream solverError;

        //final long startTime = System.nanoTime();

       //File tmpFile = null;
        std::string tmpFile = "";
        std::string stringBuffer = "";
        if (exe_path == "")
            return new Output("", "Error: executable not found");
        stringBuffer += exe_path + " " + option + " " + files_paths;
        if (final_program.length() > 0){
            tmpFile=writeToFile("tmp", final_program);
            stringBuffer += " " + tmpFile;
        }

        std::cerr<<stringBuffer<<"\n";
        CmdExecutor *executor = CmdExecutor::getInstance();
        executor->execute(stringBuffer);
/*
        Thread threadOutput=new Thread() {
            @Override
            public void run() {
                try {

                    final BufferedReader bufferedReaderOutput = new BufferedReader(new InputStreamReader(solver_process.getInputStream()));

                    // Read output of the solver and store in solverOutput
                    String currentLine;
                    while ((currentLine = bufferedReaderOutput.readLine()) != null)
                        solverOutput.append(currentLine + "\n");
                } catch (final IOException e) {
                    e.printStackTrace();
                }

            }
        };
        threadOutput.start();
        threadOutput.join();
*/
        solverOutput<<executor->getOutputStream()->rdbuf();

/*
        Thread threadError = new Thread() {
            @Override
            public void run() {
                try {

                    final BufferedReader bufferedReaderError = new BufferedReader(new InputStreamReader(solver_process.getErrorStream()));

                    String currentErrLine;
                    while ((currentErrLine = bufferedReaderError.readLine()) != null)
                        solverError.append(currentErrLine + "\n");

                } catch (final IOException e) {
                    e.printStackTrace();
                }

            }
        };
        threadError.start();
        threadError.join();
*/

        solverError<<executor->getErrorOutputStream()->rdbuf();
/*
        final PrintWriter writer = new PrintWriter(solver_process.getOutputStream());
        writer.println(final_program);
        if (writer != null)
            writer.close();
*/
        //solver_process.waitFor();

        //final long stopTime = System.nanoTime();
        //System.err.println("Total time : " + (stopTime - startTime));

        //if(tmpFile!=null) tmpFile.delete();

        return getOutput(solverOutput.str(), solverError.str());
    }

    virtual ~DesktopService() {}

protected:
    std::string exe_path;
    std::string load_from_STDIN_option;

    virtual Output* getOutput(std::string output, std::string error) = 0;

    std::string writeToFile(std::string pFilename, std::string sb) {
	    std::string tmpDir = boost::filesystem::temp_directory_path().string();
	    std::string tempFile = tmpDir + "/" + pFilename;
	    std::ofstream out(tempFile);
	    out<<sb;
	    return tempFile;
    }
};

#endif // DESKTOPSERVICE_H

};
