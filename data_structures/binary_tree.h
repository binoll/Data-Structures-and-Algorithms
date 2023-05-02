// Copyright 2023 binoll
#pragma once
#include "../libs.h"

template<typename type>
class Node {
public:
    Node() = default;  // constructor without parameters

    explicit Node(const type& value) : value(value) {};  // constructor with parameters

    ~Node() = default;  // destructor

    type value = 0;  // value
    Node<type>* left = nullptr;  // pointer to the left node
    Node<type>* right = nullptr;  // pointer to the right node
};

template<typename type>
class BinaryTree {
public:
    BinaryTree() = default;  // constructor without parameters

    explicit BinaryTree(const type& value);  // constructor with parameters

    ~BinaryTree();  // destructor

    bool find(const type& value);  // searching for an element in a binary search tree

    type findMin();  // searching min element 

    type findMax();  // searching max element

    void add(const type& value);  // add element

    void remove(const type& value);  // delete element

    void traversalNRL();  // tree traversal NRL

    void traversalLNR();  // tree traversal LNR

    void traversalRNL();  // tree traversal RNL

    bool isClear();  // checking for emptiness

    bool clear();  // cleaning the tree

    int64_t getSize() const;  // returns the current number of objects

private:
    Node<type>* root = nullptr;  // pointer to the root of the tree
    int64_t min_size = std::numeric_limits<int64_t>::min();     
    int64_t max_size = std::numeric_limits<int64_t>::max();  // maximum int64_t value
    int64_t size = 0;  // current capacity of the tree
};

template<typename type>
BinaryTree<type>::BinaryTree(const type& value) {
    try {
        if (min_size <= size <= max_size) {
            root = new Node<type>(value);
            ++size;
        } else {
            throw std::exception();
        }
    } catch (...) {
        std::cout << "\nConstruct threw except\n";
    }
}

template<typename type>
BinaryTree<type>::~BinaryTree() {
    while (root != nullptr) {
        remove(root->value);
    }
}

template<typename type>
bool BinaryTree<type>::find(const type& value) {
    Node<type>* ptr = root;

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
type BinaryTree<type>::findMin() {
    Node<type>* ptr = root;
    Node<type>* parent_ptr = root;

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
type BinaryTree<type>::findMax() {
    Node<type>* ptr = root;
    Node<type>* parent_ptr = root;

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
void BinaryTree<type>::add(const type& value) {
    Node<type>* ptr = root;

    try {
        if (root == nullptr) {
            if (min_size <= size <= max_size) {
                root = new Node<type>(value);
                ++size;
            } else {
                throw std::exception();
            }
            return;
        }
        while (true) {
            if (ptr->value > value) {
                if (ptr->left == nullptr) {
                    ptr->left = new Node<type>(value);
                    ++size;
                    return;
                } else {
                    ptr = ptr->left;
                }
            } else {
                if (ptr->right == nullptr) {
                    ptr->right = new Node<type>(value);
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
void BinaryTree<type>::remove(const type& value) {
    Node<type>* ptr = root;
    Node<type>* parent_ptr = root;
    bool is_left = true;

    if (!find(value)) {
        return;
    }

    while ((ptr != nullptr) && (ptr->value != value)) {  // search delete element
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
        if ((ptr->left == nullptr) && (ptr->right == nullptr)) {  // delete if no child
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
                Node<type>* temp = root;

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
                Node<type>* temp = root;

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
            Node<type>* successor = ptr;
            Node<type>* parent_successor = ptr;
            Node<type>* child_successor = ptr->right;

            while (child_successor != nullptr) {
                parent_successor = successor;
                successor = child_successor;
                child_successor = child_successor->left;
            }

            if (successor != ptr->right) {
                parent_successor->left = successor->right;
                ptr->value = successor->value;
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
