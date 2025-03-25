#ifndef __PROGRAM_WRAPPER_HPP__
#define __PROGRAM_WRAPPER_HPP__

#include <string>
#include <iostream>
#include "./../utils/file_utils.hpp"
#include "./../suffix-tree/suffix_tree.hpp"

class program_wrapper {
private:
    program_wrapper() {};
public:
    program_wrapper(const program_wrapper&) = delete;

    program_wrapper& operator=(const program_wrapper&) = delete;

    static program_wrapper& get_instance(void);

    void run_program(const int arg_count, const char* const* arg_vector);
};

#endif