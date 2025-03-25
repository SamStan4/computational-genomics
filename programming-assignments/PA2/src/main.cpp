#include "../include/program-wrapper/program_wrapper.hpp"

int main(int argc, char** argv) {
    program_wrapper& instance = program_wrapper::get_instance();
    instance.run_program(argc, argv);
    return 0;
}