#include "../include/program_wrapper.hpp"

program_wrapper::program_wrapper() {}

void program_wrapper::load_string(std::string& out_str, std::string& out_str_name, const char* file_path) {
    std::ifstream input_stream(file_path);
    if (!input_stream.is_open()) {
        throw std::runtime_error("Error opening input stream");
    }
    std::string buffer;
    while (std::getline(input_stream, buffer)) {
        if (buffer.empty())
            continue;
        else if (buffer[0] == '>')
            out_str_name = buffer.substr(1);
            continue;
        
    }
    input_stream.close();
}

program_wrapper& program_wrapper::get_instance(void) {
    static program_wrapper instance;
    return instance;
}