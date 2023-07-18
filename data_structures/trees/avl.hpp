// Copyright 2023 binoll
#pragma once

#include "../../libs.hpp"

template<typename type>
class Node {
 public:
    Node() = default;  // constructor without parameters

    explicit Node(const type& value);  // constructor with parameters

    int64_t getHeight() const;

    void setHeight(const int64_t& height);

    ~Node() = default;  // destructor

    int64_t height = 0;  // tree height
    type value = 0;  // value
    Node<type>* left = nullptr;  // pointer to the left node
    Node<type>* right = nullptr;  // pointer to the right node
};

template<typename type>
class AVLSearchTree {
 public:
    AVLSearchTree() = default;  // constructor without parameters

    explicit AVLSearchTree(const type& value);  // constructor with parameters

    ~AVLSearchTree();  // destructor

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
                                    const AVLSearchTree<new_type>& tree);  // print

 private:
    int64_t getHeight(Node<type>* node) const;

    void updateHeight(Node<type>* node);

    int64_t getBalance(Node<type>* node);

    void swapNodes(Node<type>* node1, Node<type>* node2);

    void rightRotate(Node<type>* node);

    void leftRotate(Node<type>* node);

    void balance(Node<type>* node);

    void print_NLR(Node<type>* node) const;

    void print_LNR(Node<type>* node) const;

    void print_RNL(Node<type>* node) const;

    void print_tree(const Node<type>* node, int tab, std::ostream& stream) const;

    Node<type>* root = nullptr;  // pointer to the root of the tree
    int64_t min_size = std::numeric_limits<int64_t>::min();  // min value
    int64_t max_size = std::numeric_limits<int64_t>::max();  // max value
    int64_t size = 0;  // current capacity of the tree
};

template<typename type>
Node<type>::Node(const type &value) : value(value) {}

template<typename type>
int64_t Node<type>::getHeight() const {
    return height;
}

template<typename type>
void Node<type>::setHeight(const int64_t& height) {
    this->heightw = height;
}

template<typename type>
AVLSearchTree<type>::AVLSearchTree(const type& value) {
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
AVLSearchTree<type>::~AVLSearchTree() {
    while (root != nullptr) {
        remove(root->value);
    }
}

template<typename type>
bool AVLSearchTree<type>::find(const type& value) const {
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
type AVLSearchTree<type>::findMin() const {
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
type AVLSearchTree<type>::findMax() const {
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
void AVLSearchTree<type>::add(const type& value) {
    Node<type>* ptr = root;
    std::stack<Node<type>*> stack;

    try {
        if (root == nullptr) {
            if (min_size <= size <= max_size) {
                root = new Node<type>(value);

                ++size;
            } else {
                throw std::exception();
            }
            return;
        } else {
            stack.push(ptr);
        }
        while (true) {
            if (ptr->value > value) {
                if (ptr->left == nullptr) {
                    ptr->left = new Node<type>(value);
                    break;
                } else {
                    ptr = ptr->left;
                    stack.push(ptr);
                }
            } else {
                if (ptr->right == nullptr) {
                    ptr->right = new Node<type>(value);
                    break;
                } else {
                    ptr = ptr->right;
                    stack.push(ptr);
                }
            }
        }
        ++size;
        while (!stack.empty()) {  // balance
            ptr = stack.top();
            updateHeight(ptr);
            balance(ptr);
            stack.pop();
        }
        return;
    } catch (...)  {
        std::cout << "\nAdd method threw except\n";
    }
}

template<typename type>
void AVLSearchTree<type>::remove(const type& value) {
    Node<type>* ptr = root;
    Node<type>* parent_ptr = root;
    bool is_left = true;
    std::stack<Node<type>*> stack;

    if (root != nullptr) {
        stack.push(root);
    } else {
        return;
    }

    while ((ptr != nullptr) &&
           (ptr->value != value)) {  // search delete element
        parent_ptr = ptr;
        stack.push(ptr);

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
            } else {
                ptr->right = successor->right;
            }

            ptr->value = successor->value;
            delete successor;
        }
        --size;

        while (!stack.empty() && (size > 2)) {  // balance
            ptr = stack.top();
            updateHeight(ptr);
            balance(ptr);
            stack.pop();
        }
    } catch (...) {
        std::cout << "\nRemove method threw except\n";
    }
}

template<typename type>
int64_t AVLSearchTree<type>::getHeight(Node<type>* node) const {
    return (node == nullptr) ? -1 : node->height;
}

template<typename type>
void AVLSearchTree<type>::updateHeight(Node<type>* node) {
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
}


template<typename type>
int64_t AVLSearchTree<type>::getBalance(Node<type>* node) {
    return (node == nullptr) ? 0 : getHeight(node->right) - getHeight(node->left);
}

template<typename type>
void AVLSearchTree<type>::swapNodes(Node<type>* node1, Node<type>* node2) {
   std::swap(node1->height, node2->height);
   std::swap(node1->value, node2->value);
}

template<typename type>
void AVLSearchTree<type>::rightRotate(Node<type>* node) {
    Node<type>* temp = node->right;
    swapNodes(node, node->left);

    node->right = node->left;
    node->left = node->right->left;
    node->right->left = node->right->right;
    node->right->right = temp;
    updateHeight(node->right);
    updateHeight(node);
}

template<typename type>
void AVLSearchTree<type>::leftRotate(Node<type>* node) {
    swapNodes(node, node->right);
    Node<type>* temp = node->left;

    node->left = node->right;
    node->right = node->left->right;
    node->left->right = node->left->left;
    node->left->left = temp;
    updateHeight(node->left);
    updateHeight(node);
}

template<typename type>
void AVLSearchTree<type>::balance(Node<type>* node) {
    int64_t balance = getBalance(node);

    if (balance == -2) {
        if (getBalance(node->left) == 1) {
            leftRotate(node->left);
        }
        rightRotate(node);
    } else if (balance == 2) {
        if (getBalance(node->right) == -1) {
            rightRotate(node->right);
        }
        leftRotate(node);
    }
}

template<typename type>
void AVLSearchTree<type>::print_NLR(Node<type> *node) const {
    if (node == nullptr) {
        return;
    }
    std::cout << node->value << " ";
    print_NLR(node->left);
    print_NLR(node->right);
}

template<typename type>
void AVLSearchTree<type>::print_LNR(Node<type> *node) const {
    if (node == nullptr) {
        return;
    }
    print_LNR(node->left);
    std::cout << node->value << " ";
    print_LNR(node->right);
}

template<typename type>
void AVLSearchTree<type>::print_RNL(Node<type> *node) const {
    if (node == nullptr) {
        return;
    }
    print_RNL(node->right);
    std::cout << node->value << " ";
    print_RNL(node->left);
}

template<typename type>
void AVLSearchTree<type>::traversalNLR() const {
    print_NLR(root);
}

template<typename type>
void AVLSearchTree<type>::traversalLNR() const {
    print_LNR(root);
}

template<typename type>
void AVLSearchTree<type>::traversalRNL() const {
    print_RNL(root);
}

template<typename type>
bool AVLSearchTree<type>::isClear() const {
    if (root == nullptr) {
        return true;
    }
    return false;
}

template<typename type>
void AVLSearchTree<type>::clear() {
    while (root != nullptr) {
        remove(root->value);
    }
}

template<typename type>
void AVLSearchTree<type>::print_tree(const Node<type>* node,
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
                         const AVLSearchTree<type>& tree) {
    if (tree.isClear()) {
        stream << "Tree is clear!\n";
    } else {
        int64_t tab = 0;

        tree.print_tree(tree.root, tab, stream);
    }
    return stream;
}

template<typename type>
int64_t AVLSearchTree<type>::getSize() const {
    return size;
}
