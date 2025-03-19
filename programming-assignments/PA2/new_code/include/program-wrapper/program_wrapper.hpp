#ifndef PROGRAM_WRAPPER_HPP
#define PROGRAM_WRAPPER_HPP

#include <string>
#include <iostream>
#include "./../utils/file_utils.hpp"

class program_wrapper {
private:
    program_wrapper() {};
public:
    program_wrapper(const program_wrapper&) = delete;

    program_wrapper& operator=(const program_wrapper&) = delete;

    static program_wrapper& get_instance(void) {
        static program_wrapper instance;
        return instance;
    }

    void run_program(const int arg_count, const char* const* arg_vector) {
        if (arg_count != 3) {
            return;
        }
        std::string gene_string;
        std::string alphabet_string;
        if (!file_utils::load_one_gene(arg_vector[1], gene_string)) {
            return;
        }
        if (!file_utils::load_alphabet(arg_vector[2], alphabet_string)) {
            return;
        }
        std::cout << gene_string << std::endl;
    }
};

#endif