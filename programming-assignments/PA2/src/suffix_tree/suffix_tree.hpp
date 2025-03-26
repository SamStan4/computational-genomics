#ifndef __SUFFIX_TREE_HPP__
#define __SUFFIX_TREE_HPP__

#include "./suffix_tree_node.hpp"

class suffix_tree {
private:
    suffix_tree_node* m_root_ptr;

    std::string m_string;
    std::string m_alphabet;

    void constructor_helper();
    void destructor_helper(suffix_tree_node*);
    void find_path_and_insert(suffix_tree_node*, i32);
    void print_tree_dfs_stdout_helper(suffix_tree_node*, std::string&);
public:
    suffix_tree(const std::string&, const std::string&);
    ~suffix_tree();
    void print_tree_dfs_stdout();
};

#endif