#include "./program_wrapper.hpp"

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
    if (!io_utils::load_alphabet(arg_vector[1], alphabet_string)) {
        std::cerr << "error loading alphabet" << std::endl;
        return;
    }
    if (!io_utils::load_one_gene(arg_vector[2], gene_string)) {
        std::cerr << "error loading gene" << std::endl;
        return;
    }
    // time_t start = clock();
    suffix_tree tree(gene_string, alphabet_string);
    // time_t end = clock();
    // double dir = ((double) end - start) / CLOCKS_PER_SEC;
    tree.print_tree_structure();
    // std::cout << dir << std::endl;

}