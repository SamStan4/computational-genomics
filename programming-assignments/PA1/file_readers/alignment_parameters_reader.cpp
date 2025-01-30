#include "./alignment_parameters_reader.hpp"

bool alignment_parameters_reader::read_alignment_parameters(const string& file_path, double& m_a, double& m_i, double& h, double& g) {
    static unordered_map<string, double> key_value = { {"match", 0}, {"mismatch", 0}, {"g", 0}, {"h", 0} };
    ifstream file(file_path);
    if (!file.is_open()) {
        return false;
    }
    string file_line;
    while (getline(file, file_line)) {
        if (file_line.empty()) {
            continue;
        }
        stringstream file_line_stream(file_line);
        string key, value;
        file_line_stream >> key >> value;
        if (key_value.find(key) != key_value.end()) {
            key_value[key] = stod(value);
        }
    }
    m_a = key_value["match"];
    m_i = key_value["mismatch"];
    h = key_value["h"];
    g = key_value["g"];
    file.close();
    return true;
}