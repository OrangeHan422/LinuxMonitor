#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <string_view>
namespace monitor{
    class ReadFile{
        public:
            explicit ReadFile(std::string_view filename)
            :m_ifs(filename.data())
            {}
            ~ReadFile(){
                m_ifs.close();
            }

            bool ReadLine(std::vector<std::string>& container);

        private:
            std::ifstream m_ifs;
    };
}