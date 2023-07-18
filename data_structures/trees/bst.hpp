// Copyright 2023 binoll
#pragma once

#include "../../libs.hpp"

template<typename type>
class TreeNode {
 public:
    TreeNode() = default;  // constructor without parameters

    explicit TreeNode(const type& value);  // constructor with parameters

    ~TreeNode() = default;  // destructor

    type value = 0;  // value
    TreeNode<type>* left = nullptr;  // pointer to the left node
    TreeNode<type>* right = nullptr;  // pointer to the right node
};

template<typename type>
class BinarySearchTree {
 public:
    BinarySearchTree() = default;  // constructor without parameters

    explicit BinarySearchTree(const type& value);  // constructor with parameters

    ~BinarySearchTree();  // destructor

    bool find(const type& value) const;  // searching for an element

    type findMin() const;  // return min element

    type findMax() const;  // return max element

    void add(const type& value);  // add element

    void remove(const type& value);  // delete element

    void traversalNLR() const;  // tree traversal NRL

    void traversalLNR() const;  // tree traversal LNR

    void traversalRNL() const;  // tree traversal RNL

    bool isClear() const;  // checking for emptiness

    void clear();  // cleaning the tree

    int64_t getSize() const;  // returns the current size of tree

    template<typename new_type>
    friend std::ostream& operator<<(std::ostream& stream,
                                    const BinarySearchTree<new_type>& tree);  // for print

 private:
    void print_NLR(TreeNode<type>* node) const;  // recursive method for traversal NRL

    void print_LNR(TreeNode<type>* node) const;  // recursive method for traversal LNR

    void print_RNL(TreeNode<type>* node) const;  // recursive method for traversal RNL

    void print_tree(const TreeNode<type>* node, int tab, std::ostream& stream) const;  // method for print tree

    TreeNode<type>* root = nullptr;  // pointer to the root of the tree
    int64_t min_size = std::numeric_limits<int64_t>::min();  // min value
    int64_t max_size = std::numeric_limits<int64_t>::max();  // max value
    int64_t size = 0;  // current capacity of the tree
};

template<typename type>
TreeNode<type>::TreeNode(const type &value) : value(value) {}

template<typename type>
BinarySearchTree<type>::BinarySearchTree(const type& value) {
    try {
        if (min_size <= size <= max_size) {
            root = new TreeNode<type>(value);

            ++size;
        } else {
            throw std::exception();
        }
    } catch (...) {
        std::cout << "\nConstruct threw except\n";
    }
}

template<typename type>
BinarySearchTree<type>::~BinarySearchTree() {
    while (root != nullptr) {
        remove(root->value);
    }
}

template<typename type>
bool BinarySearchTree<type>::find(const type& value) const {
    TreeNode<type>* ptr = root;

    while (ptr != nullptr) {
        if (ptr->value == value) {
            return true;
        } else if (ptr->value > value) {
            ptr = ptr->left;
        } else {
            ptr = ptr->right;
        }
    }
    return false;
}

template<typename type>
type BinarySearchTree<type>::findMin() const {
    TreeNode<type>* ptr = root;
    TreeNode<type>* parent_ptr = root;

    if (ptr == nullptr) {
        return NULL;
    }
    while (ptr != nullptr) {
        parent_ptr = ptr;
        ptr = ptr->left;
    }
    return parent_ptr->value;
}

template<typename type>
type BinarySearchTree<type>::findMax() const {
    TreeNode<type>* ptr = root;
    TreeNode<type>* parent_ptr = root;

    if (ptr == nullptr) {
        return NULL;
    }
    while (ptr != nullptr) {
        parent_ptr = ptr;
        ptr = ptr->right;
    }
    return parent_ptr->value;
}

template<typename type>
void BinarySearchTree<type>::add(const type& value) {
    TreeNode<type>* ptr = root;

    try {
        if (root == nullptr) {
            if (min_size <= size <= max_size) {
                root = new TreeNode<type>(value);

                ++size;
            } else {
                throw std::exception();
            }
            return;
        }
        while (true) {
            if (ptr->value > value) {
                if (ptr->left == nullptr) {
                    ptr->left = new TreeNode<type>(value);

                    ++size;
                    return;
                } else {
                    ptr = ptr->left;
                }
            } else {
                if (ptr->right == nullptr) {
                    ptr->right = new TreeNode<type>(value);

                    ++size;
                    return;
                } else {
                    ptr = ptr->right;
                }
            }
        }
    } catch (...)  {
        std::cout << "\nAdd method threw except\n";
    }
}

template<typename type>
void BinarySearchTree<type>::remove(const type& value) {
    TreeNode<type>* ptr = root;
    TreeNode<type>* parent_ptr = root;
    bool is_left = true;

    if (!find(value)) {
        return;
    }

    while ((ptr != nullptr) &&
           (ptr->value != value)) {  // search delete element
        parent_ptr = ptr;

        if (ptr->value > value) {
            is_left = true;
            ptr = ptr->left;
        } else {
            is_left = false;
            ptr = ptr->right;
        }
    }

    if (ptr == nullptr) {  // if did not search delete element
        return;
    }

    try {
        if ((ptr->left == nullptr) &&
            (ptr->right == nullptr)) {  // delete if no child
            if (ptr == root) {
                delete root;
                root = nullptr;
            } else if (is_left) {
                delete parent_ptr->left;
                parent_ptr->left = nullptr;
            } else {
                delete parent_ptr->right;
                parent_ptr->right = nullptr;
            }
        } else if (ptr->right == nullptr) {  // delete if only left child
            if (ptr == root) {
                TreeNode<type>* temp = root;

                root = ptr->left;
                delete temp;
            } else if (is_left) {
                parent_ptr->left = ptr->left;
                delete ptr;
            } else {
                parent_ptr->right = ptr->left;
                delete ptr;
            }
        } else if (ptr->left == nullptr) {  // delete if only right child
            if (ptr == root) {
                TreeNode<type>* temp = root;

                root = ptr->right;
                delete temp;
            } else if (is_left) {
                parent_ptr->left = ptr->right;
                delete ptr;
            } else {
                parent_ptr->right = ptr->right;
                delete ptr;
            }
        } else {  // delete if two child
            TreeNode<type>* successor = ptr;
            TreeNode<type>* parent_successor = ptr;
            TreeNode<type>* child_successor = ptr->right;

            while (child_successor != nullptr) {
                parent_successor = successor;
                successor = child_successor;
                child_successor = child_successor->left;
            }

            if (successor != ptr->right) {
                parent_successor->left = successor->right;
            } else {
                ptr->right = successor->right;
            }

            ptr->value = successor->value;
            delete successor;
        }
        --size;
    } catch (...) {
        std::cout << "\nRemove method threw except\n";
    }
}

template<typename type>
void BinarySearchTree<type>::print_NLR(TreeNode<type> *node) const {
    if (node == nullptr) {
        return;
    }
    std::cout << node->value << ' ';
    print_NLR(node->left);
    print_NLR(node->right);
}

template<typename type>
void BinarySearchTree<type>::print_LNR(TreeNode<type> *node) const {
    if (node == nullptr) {
        return;
    }
    print_LNR(node->left);
    std::cout << node->value << ' ';
    print_LNR(node->right);
}

template<typename type>
void BinarySearchTree<type>::print_RNL(TreeNode<type> *node) const {
    if (node == nullptr) {
        return;
    }
    print_RNL(node->right);
    std::cout << node->value << ' ';
    print_RNL(node->left);
}

template<typename type>
void BinarySearchTree<type>::traversalNLR() const {
    print_NLR(root);
}

template<typename type>
void BinarySearchTree<type>::traversalLNR() const {
    print_LNR(root);
}

template<typename type>
void BinarySearchTree<type>::traversalRNL() const {
    print_RNL(root);
}

template<typename type>
bool BinarySearchTree<type>::isClear() const {
    if (root == nullptr) {
        return true;
    }
    return false;
}

template<typename type>
void BinarySearchTree<type>::clear() {
    while (root != nullptr) {
        remove(root->value);
    }
}

template<typename type>
void BinarySearchTree<type>::print_tree(const TreeNode<type>* node,
                                        int tab, std::ostream& stream) const {
    if (node == nullptr) {
        return;
    }
    tab += 1;
    print_tree(node->right, tab, stream);
    for (int64_t i = tab; i > 0; --i) {
        stream << "    ";
    }
    stream << node->value << '\v';
    print_tree(node->left, tab, stream);
}

template<typename type>
std::ostream& operator<<(std::ostream& stream,
                         const BinarySearchTree<type>& tree) {
    if (tree.isClear()) {
        stream << "Tree is clear!\n";
    } else {
        int64_t tab = 0;

        tree.print_tree(tree.root, tab, stream);
    }
    return stream;
}

template<typename type>
int64_t BinarySearchTree<type>::getSize() const {
    return size;
}
