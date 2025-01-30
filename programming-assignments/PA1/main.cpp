#include "./file_readers/gene_sequence_reader.hpp"
#include "./file_readers/alignment_parameters_reader.hpp"

#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    string file_path = "./parameters.config";
    double a, b, c, d;
    alignment_parameters_reader::read_alignment_parameters(file_path, a, b, c, d);
    cout << a << endl << b << endl << c << endl << d << endl;
    return 0;
}