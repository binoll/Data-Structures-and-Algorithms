// Copyright 2023 binoll
#pragma once
#include "../../libs.h"

template<typename type>
class Node {
 public:
    Node() = default;  // constructor without parameters

    explicit Node(const type& value) : value(value) {}  // constructor
                                                        // with parameters
    ~Node() = default;  // destructor

    type value = 0;  // value
    Node<type>* left = nullptr;  // pointer to the left node
    Node<type>* right = nullptr;  // pointer to the right node
};

template<typename type>
class AVLTree {
 public:
    AVLTree() = default;  // constructor without parameters

    explicit AVLTree(const type& value);  // constructor with parameters

    ~AVLTree();  // destructor

    bool find(const type& value) const;  // searching for an element

    type findMin() const;  // searching min element

    type findMax() const;  // searching max element

    void add(const type& value);  // add element

    void remove(const type& value);  // delete element

    void traversalNLR() const;  // tree traversal NRL

    void traversalLNR() const;  // tree traversal LNR

    void traversalRNL() const;  // tree traversal RNL

    bool isClear() const;  // checking for emptiness

    void clear();  // cleaning the tree

    int64_t getSize() const;  // returns the current size of tree

    template<typename new_type>
    friend std::ostream& operator<<(std::ostream& stream,               // overloading an operator
                                    const AVLTree<new_type>& tree);  // to insert into a stream

 private:
    void print_NLR(Node<type>* node) const;  // recursive method for traversal NRL

    void print_LNR(Node<type>* node) const;  // recursive method for traversal LNR

    void print_RNL(Node<type>* node) const;  // recursive method for traversal RNL

    void print_tree(const Node<type>* node, int tab, std::ostream& stream) const;  // method for print tree

    Node<type>* root = nullptr;  // pointer to the root of the tree
    int64_t min_size = std::numeric_limits<int64_t>::min();  // min value
    int64_t max_size = std::numeric_limits<int64_t>::max();  // max value
    int64_t size = 0;  // current capacity of the tree
};
