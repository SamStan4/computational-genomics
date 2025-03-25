#ifndef __SUFFIX_TREE_NODE_HPP__
#define __SUFFIX_TREE_NODE_HPP__

namespace comp_genomics {
    class suffix_tree_node {
    private:
        suffix_tree_node* m_child_ptr;
        suffix_tree_node* m_sibling_ptr;
        suffix_tree_node* m_parent_ptr;
        suffix_tree_node* m_suffix_link;
    public:
        suffix_tree_node();
        ~suffix_tree_node();
        void set_child_ptr(suffix_tree_node* _child_ptr);
        void set_sibling_ptr(suffix_tree_node* _sibling_ptr);
        void set_parent_ptr(suffix_tree_node* _parent_ptr);
        void set_suffix_link(suffix_tree_node* _suffix_link);
        suffix_tree_node* get_child_ptr(void) const;
        suffix_tree_node* get_sibling_ptr(void) const;
        suffix_tree_node* get_parent_ptr(void) const;
        suffix_tree_node* get_suffix_link(void) const;

        static suffix_tree_node* get_new(void);
    };
}

#endif