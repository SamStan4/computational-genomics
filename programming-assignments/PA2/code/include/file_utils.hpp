#ifndef FILE_UTILS_HPP
#define FILE_UTILS_HPP

#include <string>
#include <fstream>

namespace file_utils {
    bool load_one_gene(const char* file_path, std::string& out_string, std::string& out_string_name) {
        std::ifstream input_stream(file_path);
        if (!input_stream.is_open()) {
            return false;
        }
        std::string buffer;
        
        input_stream.close();
    }
}


#endif