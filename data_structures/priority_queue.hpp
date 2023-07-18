// Copyright 2023 binoll
#pragma once

#include "../libs.hpp"

template<typename type>
class QueueNode {
 public:
    QueueNode() = default;  // constructor without parameters

    explicit QueueNode(const type& value,
                       const int64_t& priority);  // constructor with parameters

    ~QueueNode() = default;  // destructor

    type getValue() const;  // get value

    int64_t getPriority() const;  // get priority

    void setValue(const type& value);  // set value

    template<typename new_type>
    friend std::ostream& operator<<(std::ostream& stream,
                                    const QueueNode<new_type>& queue);  // for print

 private:
    type value;  // the value that the node stores
    int64_t priority = 0;  // node priority
};

template<typename type>
class PriorityQueue {
 public:
    PriorityQueue() = default;  // constructor without parameters

    PriorityQueue(const type& value, const int64_t& priority);  // constructor with parameters

    PriorityQueue(const PriorityQueue<type>& queue);  // copy constructor

    PriorityQueue(PriorityQueue<type>&& queue) noexcept;  // move constructor

    ~PriorityQueue();  // destructor

    void push(const type& value, const int64_t& priority);  // push element

    QueueNode<type> popMax();  //pop element with max priority

    QueueNode<type> popMin();  //pop element with min priority

    void clear();  // clear queue

    int64_t getSize() const;  // return size of the queue

    QueueNode<type> findMax() const;  // find element with max priority

    QueueNode<type> findMin() const;  // find element with max priority

    PriorityQueue<type>& operator=(const PriorityQueue<type>& queue);  // for assignment

    PriorityQueue<type>& operator=(PriorityQueue<type>&& queue) noexcept;  // for assignment with carry

    template<typename new_type>
    friend std::ostream& operator<<(std::ostream& stream,
                                    const PriorityQueue<new_type>& queue);  // for print

 private:
    void siftUp();  // for sift up

    void siftDown();  // for sift down

    int64_t size = 0;  // current capacity of the queue
    int64_t max_size = std::numeric_limits<int64_t>::max();  // maximum value
    QueueNode<type>* arr = nullptr;  // indicates the array in which the elements of the queue are stored
};

template<typename type>
QueueNode<type>::QueueNode(const type &value,
                           const int64_t &priority) : value(value), priority(priority) {}

template<typename type>
type QueueNode<type>::getValue() const {
    return value;
}

template<typename type>
int64_t QueueNode<type>::getPriority() const {
    return priority;
}

template<typename type>
void QueueNode<type>::setValue(const type& value) {
    this->value = value;
}

template<typename type>
std::ostream& operator<<(std::ostream& stream,
                         const QueueNode<type>& node) {
    stream << "{ " << node.value << ", " << node.priority << " }";
    return stream;
}

template<typename type>
PriorityQueue<type>::PriorityQueue(const type& value, const int64_t& priority) {
    try {
        arr = new QueueNode<type>[++size];
        arr[size - 1] = QueueNode<type>(value, priority);
    } catch (...) {
        std::cout << "\nProblems with constructor\n";
    }
}

template<typename type>
PriorityQueue<type>::PriorityQueue(const PriorityQueue<type>& queue) {
    try {
        this->size = queue.size;

        if (queue.size == 0) {
            delete[] arr;
            arr = nullptr;
        } else {
            delete[] arr;
            arr = new type[size];

            for (int64_t i = 0; i < size; ++i) {
                arr[i] = queue.arr[i];
            }
        }
    } catch (...) {
        std::cout << "\nProblems with copy constructor\n";
    }
}

template<typename type>
PriorityQueue<type>::PriorityQueue(PriorityQueue<type> &&queue) noexcept {
    if (this != &queue) {
        arr = queue.arr;
        size = queue.size;
        queue.arr = nullptr;
        queue.size = NULL;
    }
}

template<typename type>
PriorityQueue<type>::~PriorityQueue<type>() {
    try {
        delete[] arr;
        arr = nullptr;
        size = 0;
    } catch (...) {
        std::cout << "\nProblems with destructor!\n";
    }
}

template<typename type>
void PriorityQueue<type>::siftUp() {
    int64_t index = size - 1;

    while (arr[index].getPriority() > arr[(index - 1) / 2].getPriority()) {
        std::swap(arr[index], arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

template<typename type>
void PriorityQueue<type>::siftDown() {
    int64_t index = 0;

    while ((2 * index + 1) < size) {
        int64_t left = 2 * index + 1;
        int64_t right = 2 * index + 2;
        int64_t temp = left;

        if ((right < size) && (arr[right].getPriority() > arr[left].getPriority())) {
            temp = right;
        } else if (arr[index].getPriority() >= arr[temp].getPriority()) {
            break;
        }
        std::swap(arr[index], arr[temp]);
        index = temp;
    }
}

template<typename type>
void PriorityQueue<type>::push(const type& value, const int64_t& priority) {
    if (size == max_size) {
        std::cout << "\nProblems with push method!\n";
        return;
    }
    try {
        QueueNode<type>* new_arr = new QueueNode<type>[++size];

        for (int i = 0; i < (size - 1); ++i) {
            new_arr[i] = arr[i];
        }
        new_arr[size - 1] = QueueNode<type>(value, priority);
        delete[] arr;
        arr = new_arr;
        siftUp();
        return;
    } catch (...) {
        std::cout << "\nProblems with push method!\n";
        return;
    }
}

template<typename type>
QueueNode<type> PriorityQueue<type>::popMax() {
    if (size == 0) {
        std::cout << "\nProblems with pop method!\n";
        return QueueNode<type>(0, 0);
    }
    try {
        QueueNode<type>* new_ptr = new QueueNode<type>[--size];
        QueueNode<type> node = arr[0];

        std::swap(arr[0], arr[size]);
        for (int i = 0; i < size; ++i) {
            new_ptr[i] = arr[i];
        }
        delete[] arr;
        arr = new_ptr;
        siftUp();
        siftDown();
        return node;
    } catch (...) {
        std::cout << "\nProblems with pop method\n";
        return QueueNode<type>(0, 0);
    }
}

template<typename type>
QueueNode<type> PriorityQueue<type>::popMin() {
    QueueNode<type> node = arr[0];
    int64_t size_before = 0;
    int64_t size_after = 0;

    for (int64_t i = 0; i < size; ++i) {
        if (node.getPriority() > arr[i].getPriority()) {
            node = arr[i];
            size_before = i;
            size_after = size - (i + 1);
        }
    }

    try {
        if (size == 1) {
            --size;
            delete[] arr;
            arr = nullptr;
        } else if (size_before == 0) {
            QueueNode<type>* arr_after = new QueueNode<type>[size_after];

            for (int64_t i = 0, count = (size_before + 1); count < size; ++count, ++i) {
                arr_after[i] = arr[count];
            }

            --size;
            delete[] arr;
            arr = new QueueNode<type>[size];

            for (int64_t i = 0, count = size_before; i < size_after; ++count, ++i) {
                arr[count] = arr_after[i];
            }
            delete[] arr_after;
        } else if (size_after == 0) {
            QueueNode<type>* arr_before = new QueueNode<type>[size_before];

            for (int64_t count = 0; count < size_before; ++count) {
                arr_before[count] = arr[count];
            }

            --size;
            delete[] arr;
            arr = new QueueNode<type>[size];

            for (int64_t count = 0; count < size_before; ++count) {
                arr[count] = arr_before[count];
            }
            delete[] arr_before;
        } else {
            QueueNode<type> *ptr_before = new QueueNode<type>[size_before];
            QueueNode<type> *ptr_after = new QueueNode<type>[size_after];

            for (int64_t count = 0; count < size_before; ++count) {
                ptr_before[count] = arr[count];
            }
            for (int64_t i = 0, count = (size_before + 1); count < size; ++count, ++i) {
                ptr_after[i] = arr[count];
            }

            --size;
            delete[] arr;
            arr = new QueueNode<type>[size];

            for (int64_t count = 0; count < size_before; ++count) {
                arr[count] = ptr_before[count];
            }
            for (int64_t i = 0, count = size_before; i < size_after; ++count, ++i) {
                arr[count] = ptr_after[i];
            }
            delete[] ptr_before;
            delete[] ptr_after;
            siftUp();
            siftDown();
        }
    } catch (...) {
        std::cout << "\nProblems with remove element\n";
        return QueueNode<type>(0, 0);
    }
    return node;
}

template<typename type>
void PriorityQueue<type>::clear() {
    try {
        delete[] arr;
        arr = nullptr;
        size = 0;
    } catch (...) {
        std::cout << "\nProblems with clear method!\n";
    }
}

template<typename type>
int64_t PriorityQueue<type>::getSize() const {
    return size;
}

template<typename type>
PriorityQueue<type>& PriorityQueue<type>::operator=(const PriorityQueue<type>& queue) {
    if (this != &queue) {
        try {
            this->size = queue.size;

            delete[] arr;
            arr = new type[size];

            for (int64_t i = 0; i < size; ++i) {
                arr[i] = queue.arr[i];
            }
        } catch (...) {
            std::cout << "\nProblems with constructor\n";
        }
    }
    return *this;
}

template<typename type>
PriorityQueue<type>& PriorityQueue<type>::operator=(PriorityQueue<type>&& queue) noexcept {
    if (this != &queue) {
        arr = queue.arr;
        size = queue.size;
        queue.arr = nullptr;
        queue.size = NULL;
    }
    return *this;
}

template<typename type>
QueueNode<type> PriorityQueue<type>::findMax() const {
    return arr[0];
}

template<typename type>
QueueNode<type> PriorityQueue<type>::findMin() const {
    QueueNode<type> node = arr[0];

    for (int64_t i = 0; i < size; ++i) {
        if (node.getPriority() > arr[i].getPriority()) {
            node = arr[i];
        }
    }
    return node;
}

template<typename type>
std::ostream& operator<<(std::ostream& stream,
                         const PriorityQueue<type>& queue) {
    int64_t count = 0;

    stream << "{ ";
    if (queue.size != 0) {
        for (int64_t i = 0; i < queue.size; ++i) {
            if (count == 0) {
                stream << queue.arr[i].getValue();
            } else {
                stream << ", ";
                stream << queue.arr[i].getValue();
            }
            ++count;
        }
    }
    stream << " }";
    return stream;
}