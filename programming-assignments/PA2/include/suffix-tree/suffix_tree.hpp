#ifndef __SUFFIX_TREE_HPP__
#define __SUFFIX_TREE_HPP__

#include <iostream>
#include <string>
#include "./suffix_tree_node.hpp"

namespace comp_genomics {
    class suffix_tree {
    private:
        suffix_tree_node* m_root_ptr;
        
    public:
        suffix_tree(const std::string& alphabet, const std::string& in_string);
    };
}

#endif