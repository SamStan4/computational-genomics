#include "./wrapper/program_wrapper.hpp"

int main(int argc, char** argv) {
    int my_arg_c = 3;
    const char* my_arg_v[] = { "name", "inputs/alphabets/English_alphabet.txt", "inputs/genes/banana.txt" };
    program_wrapper& app = program_wrapper::get_instance();
    app.run_program(my_arg_c, my_arg_v);
    return 0;
}