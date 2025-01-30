#pragma once

#include <fstream>
#include <string>

using std::string;
using std::ifstream;
using std::getline;

class gene_sequence_reader {
    public:
        static bool read_gene_sequences(const string&, string&, string&);
};