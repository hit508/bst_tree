#include <vector>

#ifndef _BST_TREE_H_
#define _BST_TREE_H_

template<class key_type, typename val_type>
struct tree_node
{
    key_type key;
    val_type val;

    struct tree_node *parent;
    struct tree_node *left;
    struct tree_node *right;
};

template<typename key_type, typename val_type>
class bst_tree_imp
{
public:
    bst_tree_imp() = default;
    ~bst_tree_imp() = default;

    int insert(const key_type& key, const val_type& val, tree_node<key_type, val_type> *&root, tree_node<key_type, val_type> *&parent);
    tree_node<key_type, val_type>* search(const key_type& key, tree_node<key_type, val_type>* root);

    void adjust(tree_node<key_type, val_type>*& cur, tree_node<key_type, val_type>* next);
    int remove(const key_type& key, tree_node<key_type, val_type>*& root);
    void remove_all(tree_node<key_type, val_type>*& root);

    void visit(tree_node<key_type, val_type>* node);

    void pre_visit(tree_node<key_type, val_type> *root);
    void mid_visit(tree_node<key_type, val_type> *root);
    void lst_visit(tree_node<key_type, val_type> *root);
};

template<typename key_type, typename val_type>
class bst_tree
{
public:
    bst_tree();
    bst_tree(const std::vector<key_type>& key, const std::vector<val_type>& val);
    ~bst_tree();

    int min_search(key_type& key, val_type& val);
    int max_search(key_type& key, val_type& val);

    int search(const key_type& key, val_type& val);
    int remove(const key_type& key);
    void remove_all();
    int instert(const key_type& key, const val_type& val);

    void pre_visit();
    void mid_visit();
    void lst_visit();
private:
    tree_node<key_type, val_type> *m_tree;
    bst_tree_imp<key_type, val_type> m_bst_tree_imp;
};

template<typename key_type, typename val_type>
bst_tree<key_type, val_type>::bst_tree()
{
    m_tree = nullptr;
}

template<typename key_type, typename val_type>
bst_tree<key_type, val_type>::bst_tree(const std::vector<key_type>& key, const std::vector<val_type>& val)
{
    int num = key.size();
    if (num > val.size()) {
        num = val.size();
    }
    m_tree = nullptr;
    tree_node<key_type, val_type>* parent = nullptr;

    for (int i = 0; i < num; i++) {
        m_bst_tree_imp.insert(key[i], val[i], m_tree, parent);
    }
}

template<typename key_type, typename val_type>
bst_tree<key_type, val_type>::~bst_tree()
{
    remove_all();
}

template<typename key_type, typename val_type>
int bst_tree<key_type, val_type>::min_search(key_type& key, val_type& val)
{
    if (m_tree == nullptr) {
        return -1;
    }
    tree_node<key_type, val_type>* cur = m_tree;
    while (cur->left != nullptr) {
        cur = cur->left;
    }
    val = cur->val;
    key = cur->key;
    return 0;
}

template<typename key_type, typename val_type>
int  bst_tree<key_type, val_type>::max_search(key_type& key, val_type& val)
{
    if (m_tree == nullptr) {
        return -1;
    }

    tree_node<key_type, val_type>* cur = m_tree;
    while (cur->right != nullptr) {
        cur = cur->right;
    }
    val = cur->val;
    key = cur->key;
    return 0;
}

template<typename key_type, typename val_type>
int bst_tree<key_type, val_type>::search(const key_type& key, val_type& val)
{
    tree_node<key_type, val_type>* result_node = m_bst_tree_imp.search(key, m_tree);
    if (result_node == nullptr) {
        return -1;
    }
    val = result_node->val;
    key = result_node->key;
    return 0;
}

template<typename key_type, typename val_type>
int bst_tree<key_type, val_type>::remove(const key_type& key)
{
    return m_bst_tree_imp.remove(key, m_tree);
}

template<typename key_type, typename val_type>
void bst_tree<key_type, val_type>::remove_all()
{
    m_bst_tree_imp.remove_all(m_tree);
}

template<typename key_type, typename val_type>
int bst_tree<key_type, val_type>::instert(const key_type& key, const val_type& val)
{
    tree_node<key_type, val_type>* parent = nullptr;
    return m_bst_tree_imp.insert(key, val, m_tree, parent);
}

template<typename key_type, typename val_type>
void bst_tree<key_type, val_type>::pre_visit()
{
    m_bst_tree_imp.pre_visit(m_tree);
}

template<typename key_type, typename val_type>
void bst_tree<key_type, val_type>::mid_visit()
{
    m_bst_tree_imp.mid_visit(m_tree);
}

template<typename key_type, typename val_type>
void bst_tree<key_type, val_type>::lst_visit()
{
    m_bst_tree_imp.lst_visit(m_tree);
}

template<typename key_type, typename val_type>
void bst_tree_imp<key_type, val_type>::visit(tree_node<key_type, val_type>* node)
{
    printf("key = %d val=%d \n", node->key, node->val);
    if (node->parent != nullptr) {
        printf("parent=%d ", node->parent->key); 
    }
    if (node->left != nullptr) {
        printf("left=%d ", node->left->key); 
    }
    if (node->right != nullptr) {
        printf("right=%d ", node->right->key); 
    }
    printf("\n");
}

template<typename key_type, typename val_type>
void bst_tree_imp<key_type, val_type>::pre_visit(tree_node<key_type, val_type> *root)
{
    if (root == nullptr) {
        return;
    }
    visit(root);
    pre_visit(root->left);
    pre_visit(root->right);
}

template<typename key_type, typename val_type>
void bst_tree_imp<key_type, val_type>::mid_visit(tree_node<key_type, val_type> *root)
{
    if (root == nullptr) {
        return;
    }
    mid_visit(root->left);
    visit(root);
    mid_visit(root->right);
}

template<typename key_type, typename val_type>
void bst_tree_imp<key_type, val_type>::lst_visit(tree_node<key_type, val_type> *root)
{
    if (root == nullptr) {
        return;
    }
    lst_visit(root->left);
    lst_visit(root->right);
    visit(root);
}

template<typename key_type, typename val_type>
int bst_tree_imp<key_type, val_type>::insert(const key_type& key, const val_type& val, tree_node<key_type, val_type>*& cur_node, 
    tree_node<key_type, val_type>*& parent)
{
    if (cur_node == nullptr) {
        cur_node = new tree_node<key_type, val_type>();
        if (cur_node == nullptr) {
            return -1;
        }
        cur_node->key = key;
        cur_node->val = val;
        cur_node->left = nullptr;
        cur_node->right = nullptr;
        cur_node->parent = parent;
        if (parent != nullptr) {
        if (cur_node->key < parent->key) {
            parent->left = cur_node;
        } else {
            parent->right = cur_node;
        }
        }
        return 0;
    }
    if (key == cur_node->key) {
        printf("error: same key in the bst tree");
        return -1;
    }
    if (key < cur_node->key) {
        return insert(key, val, cur_node->left, cur_node);
    }
    return insert(key, val, cur_node->right, cur_node);
}

template<typename key_type, typename val_type>
tree_node<key_type, val_type>* bst_tree_imp<key_type, val_type>::search(const key_type& key, tree_node<key_type, val_type>* root)
{
    if (root == nullptr) {
        return nullptr;
    }

    if (key == root->key) {
        return root;
    } else {
        if (key < root->key) {
            search(key, root->left);
        } else {
            search(key, root->right);
        }
    }
}

template<typename key_type, typename val_type>
void bst_tree_imp<key_type, val_type>::adjust(tree_node<key_type, val_type>*& cur, tree_node<key_type, val_type>* next)
{
    if (cur->parent != nullptr) {
        if (cur->parent->left == cur) {
            cur->parent->left = next;
        } else {
            cur->parent->right = next;
        }
    }
    delete cur;
}

template<typename key_type, typename val_type>
int bst_tree_imp<key_type, val_type>::remove(const key_type& key, tree_node<key_type, val_type>*& root)
{
    tree_node<key_type, val_type>* cur = search(key, root);
    if (cur == nullptr) {
        return -1;
    }

    if ((cur->left == nullptr) && (cur->right == nullptr)) {
        adjust(cur, cur->left);
    } else if (cur->left == nullptr) {
        cur->right->parent = cur->parent;
        adjust(cur, cur->right);
    } else if (root->right == nullptr) {
        cur->left->parent = cur->parent;
        adjust(cur, cur->left);       
    } else {
        tree_node<key_type, val_type>* min_left = cur->right;
        while(min_left->left != nullptr) {
            min_left = min_left->left;
        }
        cur->val = min_left->val;
        cur->key = min_left->key;
        if (min_left->right != nullptr) {
            min_left->right->parent = min_left->parent;
        }
        if (min_left->parent != nullptr) {
            adjust(min_left, min_left->right);
        }
        delete min_left;
    }
    return 0;
}

template<typename key_type, typename val_type>
void bst_tree_imp<key_type, val_type>::remove_all(tree_node<key_type, val_type>*& root)
{
    if (root == nullptr) {
        return;
    }

    remove_all(root->left);
    remove_all(root->right);
    delete root;
}
#endif
