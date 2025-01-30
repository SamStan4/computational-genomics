#pragma once

#include <iostream>
#include <string>
#include "./../file_readers/alignment_parameters_reader.hpp"
#include "./../pairwise_sequence_alignment/pairwise_sequence_alignment.hpp"

using std::string;
using std::stod;
using std::cerr;
using std::endl;

class application_wrapper {
    private:
        static bool parse_out_argument_vector(int, char**, string&, int&, string&);
    public:
        static void run_application(int, char**);
};