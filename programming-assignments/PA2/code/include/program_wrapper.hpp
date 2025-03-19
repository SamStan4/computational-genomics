#ifndef PROGRAM_WRAPPER_HPP
#define PROGRAM_WRAPPER_HPP

#include "./includes.hpp"
#include "./suffix_tree.hpp"

class program_wrapper {
private:
    program_wrapper();
public:
    static program_wrapper& get_instance(void);
    static void load_string(std::string& out_str, std::string& out_str_name, const char* file_path);
    program_wrapper(const program_wrapper&) = delete;
    program_wrapper& operator=(const program_wrapper&) = delete;
};

#endif