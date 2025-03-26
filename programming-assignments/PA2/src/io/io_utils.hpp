#ifndef __IO_UTILS_HPP__
#define __IO_UTILS_HPP__

#include "./../imports.hpp"

namespace io_utils {
    bool load_one_gene(const char* file_path, std::string& out_string, std::string& out_string_name);
    bool load_one_gene(const char* file_path, std::string& out_string);
    bool load_alphabet(const char* file_path, std::string& out_string);
}

#endif