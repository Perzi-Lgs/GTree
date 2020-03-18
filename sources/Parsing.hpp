#pragma once

#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>

using namespace std;

enum class m_Evenement_type
{
    DEATH,
    BIRTH,
    WEDDING
};

struct n_data
{
    float latitude;
    float longitude;
    std::vector<int> intDate;
    m_Evenement_type type;
};

class Parsing
{
private:
    std::string load(const std::string filePath)
    {
        std::ifstream ifs(filePath);
        std::string content((std::istreambuf_iterator<char>(ifs)),
                            (std::istreambuf_iterator<char>()));
        // std::cout << content << std::endl;
        return content;
    }
public:
    Parsing() = default;
    void run(const std::string filepath, std::vector<n_data> &parsedData, m_Evenement_type type)
    {
        std::string content = load(filepath);
        std::regex word_regex("[^,;\n]+");
        std::smatch match;

        auto words_begin =
            std::sregex_iterator(content.begin(), content.end(), word_regex);
        auto words_end = std::sregex_iterator();

        std::cout << "Found "
                  << std::distance(words_begin, words_end)
                  << " numbers:\n";

        for (std::sregex_iterator i = words_begin; i != words_end; ++i)
        {
            std::string tmp = i->str();
            float tmp1 = std::atof((++i)->str().c_str());
            float tmp2 = std::atof((++i)->str().c_str());

            std::regex word_regex("[^/\n]+");
            std::smatch match;

            auto date_begin =
                std::sregex_iterator(tmp.begin(), tmp.end(), word_regex);
            auto date_end = std::sregex_iterator();
            std::vector<int> date;

            for (std::sregex_iterator i = date_begin; i != date_end; ++i) {
                date.push_back(std::stoi(i->str().c_str()));
            }

            parsedData.push_back({
                tmp1,
                tmp2,
                date,
                type
            });
        }
    }
    virtual ~Parsing() = default;
};