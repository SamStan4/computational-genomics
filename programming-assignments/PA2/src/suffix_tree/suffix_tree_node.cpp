#include "./suffix_tree_node.hpp"

suffix_tree_node::suffix_tree_node()
    : m_child_ptr(nullptr), m_sibling_ptr(nullptr),
      m_parent_ptr(nullptr), m_suffix_ptr(nullptr),
      m_start(0), m_end(0) {}

suffix_tree_node::~suffix_tree_node() {}

suffix_tree_node* suffix_tree_node::get_pointer(const std::string& reference_string, i32 position) {
    const char target_character = reference_string[position];
    suffix_tree_node* cur_ptr = this->m_child_ptr;
    while (cur_ptr) {
        if (reference_string[cur_ptr->m_start] == target_character) {
            break;
        }
        cur_ptr = cur_ptr->m_sibling_ptr;
    }
    return cur_ptr;
}