// Copyright 2023 binoll
#pragma once
#include "../libs.h"

template<typename type>
class Node {
 public:
    Node() = default;  // constructor without parameters

    explicit Node(const type& value, const int& priority);  // constructor with parameters

    type getValue() const;  // get value

    int64_t getPriority() const;  // get priority

    void setValue(const int64_t& value);  // set value

    ~Node() = default;  // destructor

 private:
    type value = 0;  // the value that the node stores
    int64_t priority = 0;  // node priority
};

template<typename type>
class PriorityQueue {
 public:
    PriorityQueue() = default;

    PriorityQueue(const type& value, const int64_t& priority);

    void push(const type& value, const int64_t& priority);

    Node<type> pop();

    ~PriorityQueue();

 private:
    void sifting(Node<type> &node);

    int64_t size = 0;  // current capacity of the queue
    int64_t max_size = std::numeric_limits<int64_t>::max();  // maximum value
    Node<type>* ptr = nullptr;  // indicates the array in which the elements of the queue are stored
};

template<typename type>
Node<type>::Node(const type &value,
                 const int &priority) : value(value), priority(priority) {}

template<typename type>
type Node<type>::getValue() const {
    return value;
}

template<typename type>
int64_t Node<type>::getPriority() const {
    return priority;
}

template<typename type>
void Node<type>::setValue(const int64_t &value) {
    this->value = value;
}

template<typename type>
PriorityQueue<type>::PriorityQueue(const type &value, const int64_t &priority) {
    try {
        ptr = new Node<type>[size + 1];

        ptr[size] = Node<type>(value, priority);
        ++size;
    } catch (...) {
        std::cout << "\nProblems with constructor\n";
    }
}

template<typename type>
void PriorityQueue<type>::sifting(Node<type> &node) {
    int64_t index = size - 1;

    while (ptr[index].getPriority() < ptr[(index - 1) / 2].getPriority()) {
        std::swap(ptr[index], ptr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

template<typename type>
void PriorityQueue<type>::push(const type &value, const int64_t &priority) {
    if (size == max_size) {
        std::cout << "\nProblems with add element, no memory!\n";
        throw std::exception();
    }
    try {
        ptr = new Node<type>[size + 1];

        ptr[size] = Node<type>(value, priority);
        sifting(ptr[size]);
        ++size;
    } catch (...) {
        std::cout << "\nProblems with add method\n";
    }
}