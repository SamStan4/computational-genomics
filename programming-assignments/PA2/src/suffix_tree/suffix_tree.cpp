#include "./suffix_tree.hpp"

void suffix_tree::constructor_helper() {
    // suffix_tree_node* active_ptr = this->m_root_ptr;
    for (i32 i = 0; i <= (i32)this->m_string.size(); ++i) {
        this->find_path_and_insert(this->m_root_ptr, i);
        // this->find_path_and_insert(active_ptr, i);
        // if (active_ptr->m_suffix_ptr) {
        //     active_ptr = active_ptr->m_suffix_ptr;
        // } else {
        //     active_ptr = m_root_ptr;
        // }
    }
}

void suffix_tree::destructor_helper(suffix_tree_node* cur_ptr) {
    if (cur_ptr == nullptr) return;
    this->destructor_helper(cur_ptr->m_sibling_ptr);
    this->destructor_helper(cur_ptr->m_child_ptr);
    delete cur_ptr;
}

void suffix_tree::find_path_and_insert(suffix_tree_node* cur_ptr, i32 position) {
    i32 i = cur_ptr->m_start;
    i32 j = cur_ptr->m_end;
    i32 k = position;
    for (; i < j && this->m_string[i] == this->m_string[k]; ++i, ++k);
    if (i == j) {
        suffix_tree_node* next_ptr = cur_ptr->get_pointer(this->m_string, k);
        if (next_ptr == nullptr) {
            suffix_tree_node* new_leaf_node_ptr = (suffix_tree_node*)new suffix_tree_node();
            new_leaf_node_ptr->m_start = k;
            new_leaf_node_ptr->m_end = (i32)this->m_string.size() + 1;
            new_leaf_node_ptr->m_sibling_ptr = cur_ptr->m_child_ptr;
            new_leaf_node_ptr->m_parent_ptr = cur_ptr;
            cur_ptr->m_child_ptr = new_leaf_node_ptr;
        } else {
            this->find_path_and_insert(next_ptr, k);
        }
    } else {
        suffix_tree_node* new_internal_node_ptr = (suffix_tree_node*)new suffix_tree_node();
        suffix_tree_node* new_leaf_node_ptr = (suffix_tree_node*)new suffix_tree_node();

        new_internal_node_ptr->m_parent_ptr = cur_ptr;
        new_leaf_node_ptr->m_parent_ptr = cur_ptr;

        new_internal_node_ptr->m_start = i;
        new_internal_node_ptr->m_end = j;

        new_leaf_node_ptr->m_start = k;
        new_leaf_node_ptr->m_end = (i32)this->m_string.size() + 1;

        new_internal_node_ptr->m_child_ptr = cur_ptr->m_child_ptr;
        cur_ptr->m_child_ptr = new_internal_node_ptr;
        cur_ptr->m_end = i;

        new_internal_node_ptr->m_sibling_ptr = new_leaf_node_ptr;

        suffix_tree_node* grandchild_ptr = new_internal_node_ptr->m_child_ptr;

        while (grandchild_ptr) {
            grandchild_ptr->m_parent_ptr = new_internal_node_ptr;
            grandchild_ptr = grandchild_ptr->m_sibling_ptr;
        }

        // if (cur_ptr->m_suffix_ptr) {
        //     new_internal_node_ptr->m_suffix_ptr = cur_ptr->m_suffix_ptr->get_pointer(this->m_string, new_internal_node_ptr->m_start);
        // }
        // cur_ptr->m_suffix_ptr = new_internal_node_ptr;
    }
}

suffix_tree::suffix_tree(const std::string& string, const std::string& alphabet)
    : m_root_ptr(new suffix_tree_node), m_string(string), m_alphabet(alphabet) {
    this->constructor_helper();
}

suffix_tree::~suffix_tree() {
    this->destructor_helper(this->m_root_ptr);
    this->m_root_ptr = nullptr;
}

void suffix_tree::print_tree_dfs_stdout() {
    std::string str;
    this->print_tree_dfs_stdout_helper(this->m_root_ptr, str);
}

void suffix_tree::print_tree_dfs_stdout_helper(suffix_tree_node* parent_ptr, std::string& str) {
    if (!parent_ptr) {
        return;
    } else if (parent_ptr->is_leaf()) {
        std::cout << str << "$" << std::endl;
        return;
    }

    const size_t origional_size = str.size();

    suffix_tree_node* cur_ptr = parent_ptr->m_child_ptr;

    while (cur_ptr) {
        str += this->m_string.substr(cur_ptr->m_start, cur_ptr->m_end - cur_ptr->m_start);
        this->print_tree_dfs_stdout_helper(cur_ptr, str);
        str.resize(origional_size);
        cur_ptr = cur_ptr->m_sibling_ptr;
    }
}