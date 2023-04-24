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

    Node<type>* findIndex(const type& value);  // searching for an element in a binary search tree

    bool add(const type& value);  // add element

    bool remove(const type& value);  // delete element

    void traversalNRL();  // tree traversal NRL

    void traversalLNR();  // tree traversal LNR

    void traversalRNL();  // tree traversal RNL

    bool isClear();  // checking for emptiness

    bool clear();  // cleaning the tree

    int64_t getSize() const;  // returns the current number of objects

private:
    Node<type>* findParentIndex(const type& value); // searching for an parent element in a binary search tree

    Node<type>* root = nullptr;  // pointer to the root of the tree
    int64_t max_size = std::numeric_limits<int64_t>::max();  // maximum int64_t value
    int64_t size = 0;  // current capacity of the tree
};

template<typename type>
BinaryTree<type>::BinaryTree(const type& value) {
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
bool BinaryTree<type>::find(const type& value) {
    Node<type>* ptr = root;

    while (true) {
        if (ptr == nullptr) {
            return false;
        } else if (ptr->value > value) {
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
Node<type>* BinaryTree<type>::findIndex(const type& value) {
    Node<type>* ptr = root;

    while (true) {
        if (ptr == nullptr) {
            return nullptr;
        } if (ptr->value > value) {
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
Node<type>* BinaryTree<type>::findParentIndex(const type& value) {
    Node<type>* parent_ptr = nullptr;
    Node<type>* chile_ptr = root;

    while (true) {
        if (chile_ptr == nullptr) {
            return nullptr;
        } if (chile_ptr->value > value) {
            if (chile_ptr->left == nullptr) {
                return nullptr;
            } else {
                parent_ptr = chile_ptr;
                chile_ptr = chile_ptr->left;
            }
        } else {
            if (chile_ptr->value == value) {
                return parent_ptr;
            } else if (chile_ptr->right == nullptr) {
                return nullptr;
            } else {
                parent_ptr = chile_ptr;
                chile_ptr = chile_ptr->right;
            }
        }
    }
}

template<typename type>
bool BinaryTree<type>::add(const type& value) {
    Node<type>* ptr = root;

    if (find(value)) {
        return false;
    } else {
        while (true) {
            if (root == nullptr) {
                try {
                    if (size <= max_size) {
                        root = new Node<type>(value);
                        ++size;
                        return true;
                    } else {
                        throw std::exception();
                    }
                } catch (...) {
                    std::cout << "\nAdd method threw except\n";
                }
            } else if (ptr->value > value) {
                if (ptr->left == nullptr) {
                    try {
                        if (size <= max_size) {
                            ptr->left = new Node<type>(value);
                            ++size;
                            return true;
                        } else {
                            throw std::exception();
                        }
                    } catch (...) {
                        std::cout << "\nAdd method threw except\n";
                    }
                } else {
                    ptr = ptr->left;
                }
            } else if (ptr->value < value) {
                if (ptr->right == nullptr) {
                    try {
                        if (size <= max_size) {
                            ptr->right = new Node<type>(value);
                            ++size;
                            return true;
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
    }
}

template<typename type>
bool BinaryTree<type>::remove(const type& value) {
    Node<type>* ptr = findIndex(value);

    if (ptr != nullptr) {
        if ((ptr->left == nullptr) && (ptr->right == nullptr)) {
            Node<type>* parent_ptr = findParentIndex(value);
            Node<type>* child_ptr = ptr;

            if (parent_ptr == nullptr) {
                try {
                    delete child_ptr;
                    --size;
                } catch (...) {
                    std::cout << "\nRemove method threw except\n";
                }
            } else {
                if ((parent_ptr->left != nullptr) && (parent_ptr->left->value == value)) {
                    try {
                        parent_ptr->left = nullptr;
                        delete child_ptr;
                        --size;
                    } catch (...) {
                        std::cout << "\nRemove method threw except\n";
                    }
                } else if ((parent_ptr->right != nullptr) && (parent_ptr->right->value == value)) {
                    try {
                        parent_ptr->right = nullptr;
                        delete child_ptr;
                        --size;
                    } catch (...) {
                        std::cout << "\nRemove method threw except\n";
                    }
                }
            }
            return true;
        } else if ((ptr->left != nullptr) && (ptr->right != nullptr)) {
            Node<type>* parent_ptr = ptr;
            Node<type>* child_ptr = ptr->right;
            type temp = 0;

            while (true) {
                if (child_ptr->left == nullptr) {
                    temp = child_ptr->value;

                    if (remove(child_ptr->value)) {
                        parent_ptr->left = nullptr;
                        ptr->value = temp;
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    parent_ptr = child_ptr;
                    child_ptr = child_ptr->left;
                }
            }
        } else if ((ptr->left != nullptr) || (ptr->right != nullptr)) {
            Node<type>* parent_ptr = findParentIndex(value);
            Node<type>* child_ptr = ptr;

            if (child_ptr->left != nullptr) {
                if ((parent_ptr->left != nullptr) && (parent_ptr->left->value == value)) {
                    try {
                        parent_ptr->left = child_ptr->left;
                        delete child_ptr;
                        --size;
                    } catch (...) {
                        std::cout << "\nRemove method threw except\n";
                    }
                } else if ((parent_ptr->right != nullptr) && (parent_ptr->right->value == value)) {
                    try {
                        parent_ptr->right = child_ptr->right;
                        delete child_ptr;
                        --size;
                    } catch (...) {
                        std::cout << "\nRemove method threw except\n";
                    }
                }
            } else if (child_ptr->right != nullptr) {
                if ((parent_ptr->left != nullptr) && (parent_ptr->left->value == value)) {
                    try {
                        parent_ptr->left = child_ptr->left;
                        delete child_ptr;
                        --size;
                    } catch (...) {
                        std::cout << "\nRemove method threw except\n";
                    }
                } else if ((parent_ptr->right != nullptr) && (parent_ptr->right->value == value)) {
                    try {
                        parent_ptr->right = child_ptr->right;
                        delete child_ptr;
                        --size;
                    } catch (...) {
                        std::cout << "\nRemove method threw except\n";
                    }
                }
            }
            return true;
        }
    } else {
        return false;
    }
}