#ifndef __SUFFIX_TREE_NODE_HPP__
#define __SUFFIX_TREE_NODE_HPP__

#include "./../imports.hpp"

class suffix_tree;

class suffix_tree_node {
private:
    suffix_tree_node* m_child_ptr;
    suffix_tree_node* m_sibling_ptr;
    suffix_tree_node* m_parent_ptr;
    suffix_tree_node* m_suffix_ptr;

    i32 m_start;
    i32 m_end;

    friend class suffix_tree;
public:
    suffix_tree_node();
    ~suffix_tree_node();
    suffix_tree_node* get_pointer(const std::string& reference_string, i32 position);
};

#endif