#include "./../../include/program-wrapper/program_wrapper.hpp"

program_wrapper& program_wrapper::get_instance(void) {
    static program_wrapper instance;
    return instance;
}

void program_wrapper::run_program(const int arg_count, const char* const* arg_vector) {
    if (arg_count != 3) {
        std::cerr << "incorrect command line args, exiting" << std::endl;
        return;
    }
    std::string gene_string;
    std::string alphabet_string;
    if (!file_utils::load_one_gene(arg_vector[1], gene_string)) {
        return;
    }
    if (!file_utils::load_alphabet(arg_vector[2], alphabet_string)) {
        return;
    }
    comp_genomics::suffix_tree(alphabet_string, gene_string);
}