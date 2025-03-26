#ifndef __SUFFIX_TREE_HPP__
#define __SUFFIX_TREE_HPP__

#include "./suffix_tree_node.hpp"

class suffix_tree {
private:
    suffix_tree_node* m_root_ptr;

    std::string m_string;
    std::string m_alphabet;

    void constructor_helper();
    void destructor_helper(suffix_tree_node* cur_ptr);
    void find_path_and_insert(suffix_tree_node* cur_ptr, i32 position);
public:
    suffix_tree(const std::string& string, const std::string& alphabet);
    ~suffix_tree();
};

#endif