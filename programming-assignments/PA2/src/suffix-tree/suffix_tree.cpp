#include "./../../include/suffix-tree/suffix_tree.hpp"

namespace comp_genomics {
    suffix_tree::suffix_tree(const std::string& alphabet, const std::string& in_string) 
    : m_root_ptr(nullptr) {
        std::cout << "inside of constructor" << std::endl;
    }
}
