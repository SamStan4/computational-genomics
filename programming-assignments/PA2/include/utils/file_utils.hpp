#ifndef __FILE_UTILS_HPP__
#define __FILE_UTILS_HPP__

#include <string>
#include <fstream>
#include <unordered_set>
#include <algorithm>
#include <cctype>

namespace file_utils {
    bool load_one_gene(const char* file_path, std::string& out_string, std::string& out_string_name);

    bool load_one_gene(const char* file_path, std::string& out_string);

    bool load_alphabet(const char* file_path, std::string& out_string);
}

#endif