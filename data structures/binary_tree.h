// Copyright 2023 binoll
#pragma once
#include "libs.h"

template<typename type>
class Node {
public:
    Node() = default;  // constructor without parameters

    explicit Node(type& value) : value(value) {};  // constructor with parameters

    ~Node() = default;  // destructor

private:
    type value = 0;  // value
    Node<type>* left = nullptr;  // pointer to the left node
    Node<type>* right = nullptr;  // pointer to the right node
};

template<typename type>
class BinaryTree {
public:
    BinaryTree();  // constructor without parameters

    explicit BinaryTree(type& value);  // constructor with parameters

    ~BinaryTree();  // destructor

    bool find(type& value);  // searching for an element in a binary search tree

    Node<type>* findIndex(type& value);  // searching for an element in a binary search tree

    bool add(type& value);  // add element

    bool remove(type& value);  // delete element

    void traversalNRL();  // tree traversal NRL

    void traversalLNR();  // tree traversal LNR

    void traversalRNL();  // tree traversal RNL

    bool isClear();  // checking for emptiness

    bool clear();  // cleaning the tree

    int64_t getSize() const;  // returns the current number of objects

private:
    Node<type>* root = nullptr;  // pointer to the root of the tree
    int64_t max_size = std::numeric_limits<int64_t>::max();  // maximum int64_t value
    int64_t size = 0;  // current capacity of the tree
};

template<typename type>
BinaryTree<type>::BinaryTree() {
    try {
        if (size <= max_size) {
            root = new Node<type>();
            ++size;
        } else {
            throw std::exception();
        }
    } catch (...) {
        std::cout << "\nConstruct threw except\n";
    }
}

template<typename type>
BinaryTree<type>::BinaryTree(type& value) {
    try {
        if (size <= max_size) {
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

}

template<typename type>
bool BinaryTree<type>::find(type& value) {
    Node<type>* ptr = root;

    while (true) {
        if (ptr->value > value) {
            if (ptr->left == nullptr) {
                return false;
            } else {
                ptr = ptr->left;
            }
        } else {
            if (ptr->value == value) {
                return true;
            } else if (ptr->right == nullptr) {
                return false;
            } else {
                ptr = ptr->right;
            }
        }
    }
}

template<typename type>
Node<type>* BinaryTree<type>::findIndex(type& value) {
    Node<type>* ptr = root;

    while (true) {
        if (ptr->value > value) {
            if (ptr->left == nullptr) {
                return nullptr;
            } else {
                ptr = ptr->left;
            }
        } else {
            if (ptr->value == value) {
                return ptr;
            } else if (ptr->right == nullptr) {
                return nullptr;
            } else {
                ptr = ptr->right;
            }
        }
    }
}

template<typename type>
bool BinaryTree<type>::add(type& value) {
    Node<type>* ptr = root;

    if (!find(value)) {
        while (true) {
            if (ptr->value > value) {
                if (ptr->left == nullptr) {
                    try {
                        if (size <= max_size) {
                            ptr->left = new Node<type>(value);
                            ++size;
                        } else {
                            throw std::exception();
                        }
                    } catch (...) {
                        std::cout << "\nAdd method threw except\n";
                    }
                } else {
                    ptr = ptr->left;
                }
            } else {
                if (ptr->right == nullptr) {
                    try {
                        if (size <= max_size) {
                            ptr->right = new Node<type>(value);
                            ++size;
                        } else {
                            throw std::exception();
                        }
                    } catch (...) {
                        std::cout << "\nAdd method threw except\n";
                    }
                } else {
                    ptr = ptr->right;
                }
            }
        }
    } else {
        return false;
    }
}