#include "./../../include/suffix-tree/suffix_tree_node.hpp"

namespace comp_genomics {
    suffix_tree_node::suffix_tree_node() 
    : m_child_ptr(nullptr), m_sibling_ptr(nullptr),
      m_parent_ptr(nullptr), m_suffix_link(nullptr) {}

    suffix_tree_node::~suffix_tree_node() {}

    void suffix_tree_node::set_child_ptr(suffix_tree_node* _child_ptr) {
        this->m_child_ptr = _child_ptr;
    }

    void suffix_tree_node::set_sibling_ptr(suffix_tree_node* _sibling_ptr) {
        this->m_sibling_ptr = _sibling_ptr;
    }

    void suffix_tree_node::set_parent_ptr(suffix_tree_node* _parent_ptr) {
        this->m_parent_ptr = _parent_ptr;
    }

    void suffix_tree_node::set_suffix_link(suffix_tree_node* _suffix_link) {
        this->m_suffix_link = _suffix_link;
    }

    suffix_tree_node* suffix_tree_node::get_child_ptr(void) const {
        return this->m_child_ptr;
    }

    suffix_tree_node* suffix_tree_node::get_sibling_ptr(void) const {
        return this->m_sibling_ptr;
    }

    suffix_tree_node* suffix_tree_node::get_parent_ptr(void) const {
        return this->m_parent_ptr;
    }

    suffix_tree_node* suffix_tree_node::get_suffix_link(void) const {
        return this->m_suffix_link;
    }

    suffix_tree_node* suffix_tree_node::get_new(void) {
        return new suffix_tree_node();
    }
}