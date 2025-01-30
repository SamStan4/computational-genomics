#pragma once

#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>

using std::string;
using std::ifstream;
using std::getline;
using std::unordered_map;
using std::stringstream;

class alignment_parameters_reader {
    public:
    static bool read_alignment_parameters(const string&, double&, double&, double&, double&);
};