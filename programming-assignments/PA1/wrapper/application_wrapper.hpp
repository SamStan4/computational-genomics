#pragma once

#include <string>

using std::string;
using std::stod;

class application_wrapper {
    private:
        static bool parse_out_argument_vector(int, char**, string&, int&, string&);
    public:
        static void run_application(int, char**);
};