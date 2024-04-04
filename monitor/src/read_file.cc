#include "read_file.h"
namespace monitor{
bool ReadFile::ReadLine(std::vector<std::string>& container){
    std::string line;
    std::getline(m_ifs,line);
    if(m_ifs.eof() || line.empty()){
        return false;
    }

    std::istringstream iss(line);
    while(!iss.eof()){
        std::string word;
        iss >> word;
        container.emplace_back(std::move(word));
    }

    // for(const auto& word:container){
    //     std::cout << word << std::endl;
    // }

    return true;
}
}// namespace monitor
