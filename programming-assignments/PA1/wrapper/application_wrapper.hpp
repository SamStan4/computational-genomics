#pragma once

#include <iostream>
#include <string>

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