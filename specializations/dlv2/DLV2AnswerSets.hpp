#include "../../languages/asp/AnswerSets.hpp"
#include "../../languages/asp/AnswerSet.hpp"
#include <regex>

namespace embasp {

#ifndef DLV2ANSWERSETS_H
#define DLV2ANSWERSETS_H

class DLV2AnswerSets : public AnswerSets
{
public:

    DLV2AnswerSets(const std::string &answersets): AnswerSets(answersets) { }

    DLV2AnswerSets(const std::string &out, const std::string &err): AnswerSets(out, err) { }

    virtual ~DLV2AnswerSets() {}

protected:
    void parse() {
		bool optimum = output.find("OPTIMUM") != std::string::npos;

		/* C++ problems with multiline regexp */
		size_t pos = 0;
		while((pos = output.find('\n')) != std::string::npos) {
			output.replace(pos, 1, "\\n");
		}

		//final Pattern pattern = !optimum ? Pattern.compile("ANSWER\\r?\\n(.*)") : Pattern.compile("ANSWER\\r?\\n(.*)(\\r?\\nCOST (.+)\\r?\\nOPTIMUM)");
        std::regex pattern = !optimum ? std::regex(R"(ANSWER\\n([-a-zA-z0-9\.\(\) ]*)(\\n)?)") : std::regex(R"(ANSWER\\n([-a-zA-z0-9 .\(\)]*?) \\nCOST ((\d+@\d+\s?)+)\\nOPTIMUM(\\n)?)");
		//final Matcher matcher = pattern.matcher(output);
        std::sregex_iterator matcher_it(output.begin(), output.end(), pattern);

		while (matcher_it != std::sregex_iterator()) {
            std::smatch matcher = *matcher_it;

			std::regex patternAnswerSet(R"((-?[a-z][A-Za-z0-9_]*(\(.*?\)))\.\s*?(\\n)?)");//c++ does not support multiline regexp[c++17 has multiline support, but it is not implemented yet]
			std::string matchedAnswerset = matcher.str(1);

			std::sregex_iterator matcherAnswerSet_it(matchedAnswerset.begin(), matchedAnswerset.end(), patternAnswerSet);
			std::list<std::string> answerSetList;
			while (matcherAnswerSet_it != std::sregex_iterator()) {
                std::smatch matcherAnswerSet = *matcherAnswerSet_it;
				answerSetList.push_back(matcherAnswerSet.str(1));
				matcherAnswerSet_it++;
            }

			if (optimum) {

				std::unordered_map<int, int> weightMap;

                std::string s = matcher.str(2);

                std::string delimiter = " ";
                size_t pos = 0;
                std::string token;

                while ((pos = s.find(delimiter)) != std::string::npos) {
                    token = s.substr(0, pos);

                    size_t delimIndex = token.find("@");

                    weightMap.insert_or_assign(std::stoi(token.substr(delimIndex + 1)), std::stoi(token.substr(0, delimIndex)));

                    s.erase(0, pos + delimiter.length());
                }

				size_t delimIndex = s.find("@");
				weightMap.insert_or_assign(std::stoi(s.substr(delimIndex + 1)), std::stoi(s.substr(0, delimIndex)));

				answersets.push_back(new AnswerSet(answerSetList, weightMap));

			} else
				answersets.push_back(new AnswerSet(answerSetList));
			matcher_it++;
		}

    }

};

#endif // DLV2ANSWERSETS_H

};
