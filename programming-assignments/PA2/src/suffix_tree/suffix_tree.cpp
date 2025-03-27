#include "./suffix_tree.hpp"

void suffix_tree::constructor_helper() {
    // Hot pointer is the most recently created leaf node in the tree
    suffix_tree_node* hot_ptr = this->m_root_ptr;
    for (i32 i = 0; i <= (i32)this->m_string.size(); ++i) {
        this->find_path_and_insert(this->m_root_ptr, i, 0, hot_ptr);
        // suffix_tree_node* suffix_link = hot_ptr->m_parent_ptr->m_suffix_ptr;
        // if (suffix_link) {
        //     // case 1
        //     this->find_path_and_insert(suffix_link, i + suffix_link->m_depth, suffix_link->m_depth, hot_ptr);
        // } else {
        //     // case 2
        //     this->find_path_and_insert(this->m_root_ptr, i, 0, hot_ptr);
        // }
    }
}

void suffix_tree::destructor_helper(suffix_tree_node* cur_ptr) {
    if (cur_ptr == nullptr) return;
    this->destructor_helper(cur_ptr->m_sibling_ptr);
    this->destructor_helper(cur_ptr->m_child_ptr);
    delete cur_ptr;
}

void suffix_tree::find_path_and_insert(suffix_tree_node* cur_ptr, i32 position, i32 depth, suffix_tree_node*& hot_ptr) {
    i32 i = cur_ptr->m_start;
    i32 j = cur_ptr->m_end;
    i32 k = position;
    for (; i < j && this->m_string[i] == this->m_string[k]; ++i, ++k);
    if (i == j) {
        suffix_tree_node* next_ptr = cur_ptr->get_pointer(this->m_string, k);
        if (next_ptr == nullptr) {
            suffix_tree_node* new_leaf_node_ptr = new suffix_tree_node();
            new_leaf_node_ptr->m_start = k;
            new_leaf_node_ptr->m_end = (i32)this->m_string.size() + 1;
            new_leaf_node_ptr->m_depth = depth + ((i32)this->m_string.size() + 1 - position);
            new_leaf_node_ptr->m_sibling_ptr = cur_ptr->m_child_ptr;
            new_leaf_node_ptr->m_parent_ptr = cur_ptr;
            cur_ptr->m_child_ptr = new_leaf_node_ptr;
            hot_ptr = new_leaf_node_ptr;
        } else {
            this->find_path_and_insert(next_ptr, k, depth + (cur_ptr->m_end - cur_ptr->m_start), hot_ptr);
        }
    } else {
        // suffix_tree_node* new_internal_node_ptr = new suffix_tree_node();
        // suffix_tree_node* new_leaf_node_ptr = new suffix_tree_node();

        // new_internal_node_ptr->m_parent_ptr = cur_ptr;
        // new_leaf_node_ptr->m_parent_ptr = cur_ptr;

        // new_internal_node_ptr->m_start = i;
        // new_internal_node_ptr->m_end = j;
        // new_internal_node_ptr->m_depth = cur_ptr->m_depth;

        // new_leaf_node_ptr->m_start = k;
        // new_leaf_node_ptr->m_end = (i32)this->m_string.size() + 1;
        // new_leaf_node_ptr->m_depth = depth + ((i32)this->m_string.size() + 1 - position);

        // new_internal_node_ptr->m_child_ptr = cur_ptr->m_child_ptr;
        // cur_ptr->m_child_ptr = new_internal_node_ptr;
        // cur_ptr->m_end = i;
        // cur_ptr->m_depth -= (j - i);

        // new_internal_node_ptr->m_sibling_ptr = new_leaf_node_ptr;

        // suffix_tree_node* grandchild_ptr = new_internal_node_ptr->m_child_ptr;

        // // This is gonna get expensive
        // while (grandchild_ptr) {
        //     grandchild_ptr->m_parent_ptr = new_internal_node_ptr;
        //     grandchild_ptr = grandchild_ptr->m_sibling_ptr;
        // }

        // hot_ptr = new_leaf_node_ptr;

        suffix_tree_node* new_internal_node_ptr = new suffix_tree_node();
        suffix_tree_node* new_leaf_node_ptr = new suffix_tree_node();

        new_leaf_node_ptr->m_start = k;
        new_leaf_node_ptr->m_end = (i32)this->m_string.size() + 1;
        new_leaf_node_ptr->m_depth = depth + ((i32)this->m_string.size() + 1 - position);

        new_internal_node_ptr->m_start = cur_ptr->m_start;
        new_internal_node_ptr->m_end = i;
        new_internal_node_ptr->m_depth = cur_ptr->m_depth - (j - i);

        cur_ptr->m_start = i;

        new_internal_node_ptr->m_sibling_ptr = cur_ptr->m_sibling_ptr;
        new_internal_node_ptr->m_parent_ptr = cur_ptr->m_parent_ptr;
        new_internal_node_ptr->m_child_ptr = cur_ptr;

        if (cur_ptr->m_parent_ptr->m_child_ptr == cur_ptr) {
            cur_ptr->m_parent_ptr->m_child_ptr = new_internal_node_ptr;
        } else {
            suffix_tree_node* cur_child_ptr = cur_ptr->m_parent_ptr->m_child_ptr;
            while (cur_child_ptr) {
                if (cur_child_ptr->m_sibling_ptr == cur_ptr) {
                    cur_child_ptr->m_sibling_ptr = new_internal_node_ptr;
                    break;
                }
                cur_child_ptr = cur_child_ptr->m_sibling_ptr;
            }
        }

        cur_ptr->m_sibling_ptr = new_leaf_node_ptr;
        cur_ptr->m_parent_ptr = new_internal_node_ptr;

        new_leaf_node_ptr->m_parent_ptr = new_internal_node_ptr;

        hot_ptr = new_leaf_node_ptr;
    }
}

suffix_tree::suffix_tree(const std::string& string, const std::string& alphabet)
    : m_root_ptr(new suffix_tree_node), m_string(string), m_alphabet(alphabet) {
    this->m_root_ptr->m_suffix_ptr = this->m_root_ptr;
    this->m_root_ptr->m_parent_ptr = this->m_root_ptr;
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

void suffix_tree::print_tree_structure() {
    std::string str1;
    std::string str2;
    this->print_tree_structure_helper(this->m_root_ptr, str1, str2);
}

void suffix_tree::print_tree_structure_helper(suffix_tree_node* cur_ptr, std::string& prefix, std::string& suffix) {
    if (cur_ptr == nullptr) {
        return;
    }

    std::cout << prefix;
    std::cout << (!cur_ptr->m_sibling_ptr ? "└── " : "├── ");
    
    std::cout << (cur_ptr->is_leaf() ? "[Leaf]" : "[Internal]") 
              << " (" << cur_ptr->m_start << ", " << cur_ptr->m_end << ", " << cur_ptr->m_depth << ")";
    if (cur_ptr->is_leaf()) {
        std::cout << " \"" << suffix << "$\"";
    }
    std::cout << std::endl;

    const size_t prefix_size = prefix.size();

    prefix += (!cur_ptr->m_sibling_ptr ? "    " : "│   ");

    suffix_tree_node* cur_child = cur_ptr->m_child_ptr;

    const size_t suffix_cur_size = suffix.size();

    while (cur_child) {
        suffix += this->m_string.substr(cur_child->m_start, cur_child->m_end - cur_child->m_start);
        this->print_tree_structure_helper(cur_child, prefix, suffix);
        suffix.resize(suffix_cur_size);
        cur_child = cur_child->m_sibling_ptr;
    }

    prefix.resize(prefix_size);
}

void suffix_tree::get_number_leaves_helper(suffix_tree_node* cur_ptr, i32& num_leaves) {
    if (!cur_ptr) {
        return;
    } else if (cur_ptr->is_leaf()) {
        ++num_leaves;
    }

    this->get_number_leaves_helper(cur_ptr->m_sibling_ptr, num_leaves);
    this->get_number_leaves_helper(cur_ptr->m_child_ptr, num_leaves);
}

i32 suffix_tree::get_number_leaves() {
    i32 res = 0;
    this->get_number_leaves_helper(this->m_root_ptr, res);
    return res;
}

void suffix_tree::get_number_internas_helper(suffix_tree_node* cur_ptr, i32& num_internals) {
    if (!cur_ptr) {
        return;
    } else if (!cur_ptr->is_leaf()) {
        ++num_internals;
    }

    this->get_number_internas_helper(cur_ptr->m_sibling_ptr, num_internals);
    this->get_number_internas_helper(cur_ptr->m_child_ptr, num_internals);
}

i32 suffix_tree::get_number_internas() {
    i32 res = 0;
    this->get_number_internas_helper(this->m_root_ptr, res);
    return res;
}