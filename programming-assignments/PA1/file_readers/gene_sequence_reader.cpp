#include "./gene_sequence_reader.hpp"

bool gene_sequence_reader::read_gene_sequences(const string& file_path, string& s1, string& s2) {
    s1.clear();
    s2.clear();
    ifstream file(file_path);
    if (!file.is_open()) {
        return false;
    }
    string file_line;
    string* current_sequence = nullptr;
    while (getline(file, file_line)) {
        if (file_line.empty()) {
            continue;
        }
        if (file_line[0] == '>') {
            if (current_sequence == nullptr) {
                current_sequence = &s1;
            } else {
                current_sequence = &s2;
            }
            continue;
        }
        if (current_sequence) {
            *current_sequence += file_line;
        }
    }
    file.close();
    return !(s1.empty() || s2.empty());
}