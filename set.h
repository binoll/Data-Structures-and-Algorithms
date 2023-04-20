// Copyright 2023 binoll
#pragma once
#include <bits/stdc++.h>

template<typename type>
class Set {
public:
    Set() = default; // constructor without parameters

    explicit Set(const type& value); // constructor with parameters

    explicit Set(const ssize_t& size); // constructor with parameters

    Set(const Set& set); // copy constructor

    Set(Set&& set) noexcept; // move constructor

    ~Set(); // destructor

    bool find(const type& value) const; // item search, return bool

    ssize_t findIndex(const type& value) const; // item search, return index
                                                // (if element is not in set then -1)
    bool add(const type& value); // adding an element to a set

    bool remove(const type& value); // removing an element from a set

    void clear(); // clear set

    ssize_t getSize() const; // the method returns the current size of the set

    Set& operator=(const Set& set); // overloading the operator for assignment

    Set& operator=(Set&& set) noexcept; // operator overloading for assignment with carry

    Set operator*(const Set& set); // operator overload for the intersection of two sets

    Set operator+(const Set& set); // operator overload for combining two sets

    Set operator-(const Set& set); // operator overload for the difference of two sets

    template<typename new_type>
    friend std::ostream& operator<<(std::ostream& stream, const Set<new_type>& set); // overloading
                                                                                     // an operator to insert into a stream
private:
    ssize_t size = 0; // current capacity of the set
    ssize_t max_size = std::numeric_limits<ssize_t>::max(); // maximum ssize_t value
    type *ptr = nullptr; // indicates the array in which the elements of the set are stored
};

template<typename type>
Set<type>::Set(const type &value) {
    ssize_t index = size;

    try {
        ptr = new type[size];

        ptr[index] = value;
        ++size;
    } catch (...) {
        std::cout << "\nProblems with constructor\n";
    }
}

template<typename type>
Set<type>::Set(const ssize_t &size) {
    try {
        ptr = new type[size];

        for (ssize_t i = 0; i < size; ++i) {
            ptr[i] = 0;
        }
    } catch (...) {
        std::cout << "\nProblems with constructor\n";
    }
}

template<typename type>
Set<type>::Set(const Set &set) {
    this->size = set.size;

    try {
        delete[] ptr;
        ptr = new type[size];

        for (ssize_t i = 0; i < size; ++i) {
            ptr[i] = set.ptr[i];
        }
    } catch (...) {
        std::cout << "\nProblems with copy constructor\n";
    }
}

template<typename type>
Set<type>::Set(Set &&set) noexcept {
    ptr = set.ptr;
    size = set.size;
    set.ptr = nullptr;
    set.size = 0;
}

template<typename type>
Set<type>::~Set() {
    try {
        delete[] ptr;
    } catch (...) {
        std::cout << "\nProblems with destructor\n";
    }
}

template<typename type>
bool Set<type>::find(const type &value) const {
    for (ssize_t i = 0; i < size; ++i) {
        if (ptr[i] == value) {
            return true;
        }
    }
    return false;
}

template<typename type>
ssize_t Set<type>::findIndex(const type &value) const {
    for (ssize_t i = 0; i < size; ++i) {
        if (ptr[i] == value) {
            return i;
        }
    }
    return -1;
}

template<typename type>
bool Set<type>::add(const type &value) {
    if (size == max_size) {
        std::cout << "\nProblems with add element, no memory!\n";
        return false;
    } else if (findIndex(value) == -1) {
        if (ptr == nullptr) {
            try {
                ssize_t index = size;

                ++size;
                ptr = new type[size];
                ptr[index] = value;
            } catch (...) {
                std::cout << "\nProblems with add element\n";
                return false;
            }
        } else {
            type *new_ptr = ptr;
            ssize_t index = size;

            try {
                ++size;
                ptr = nullptr;
                ptr = new type[size];
            } catch (...) {
                std::cout << "\nProblems with add element\n";
                return false;
            }

            for (ssize_t i = 0; i < index; ++i) {
                ptr[i] = new_ptr[i];
            }
            ptr[index] = value;

            try {
                delete[] new_ptr;
            } catch (...) {
                std::cout << "\nProblems with add element\n";
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

template<typename type>
bool Set<type>::remove(const type &value) {
    ssize_t index = findIndex(value);
    ssize_t size_after = size - (index + 1);
    ssize_t size_before = index;


    if (index != -1) {
        if (size == 1) {
            try {
                --size;
                delete[] ptr;
                ptr = nullptr;
            } catch (...) {
                std::cout << "\nProblems with remove element\n";
                return false;
            }
        } else if (size_before == 0) {
            try {
                type *ptr_after = new type[size_after];

                for (ssize_t i = 0, count = (size_before + 1); count < size; ++count, ++i) {
                    ptr_after[i] = ptr[count];
                }

                --size;
                delete[] ptr;
                ptr = new type[size];

                for (ssize_t i = 0, count = size_before; i < size_after; ++count, ++i) {
                    ptr[count] = ptr_after[i];
                }

                delete[] ptr_after;
            } catch (...) {
                std::cout << "\nProblems with remove element\n";
                return false;
            }
        } else if (size_after == 0) {
            try {
                type *ptr_before = new type[size_before];

                for (ssize_t count = 0; count < size_before; ++count) {
                    ptr_before[count] = ptr[count];
                }

                --size;
                delete[] ptr;
                ptr = new type[size];

                for (ssize_t count = 0; count < size_before; ++count) {
                    ptr[count] = ptr_before[count];
                }

                delete[] ptr_before;
            } catch (...) {
                std::cout << "\nProblems with remove element\n";
                return false;
            }
        } else {
            try {
                type *ptr_before = new type[size_before];
                type *ptr_after = new type[size_after];

                for (ssize_t count = 0; count < size_before; ++count) {
                    ptr_before[count] = ptr[count];
                }
                for (ssize_t i = 0, count = (size_before + 1); count < size; ++count, ++i) {
                    ptr_after[i] = ptr[count];
                }

                --size;
                delete[] ptr;
                ptr = new type[size];

                for (ssize_t count = 0; count < size_before; ++count) {
                    ptr[count] = ptr_before[count];
                }
                for (ssize_t i = 0, count = size_before; i < size_after; ++count, ++i) {
                    ptr[count] = ptr_after[i];
                }

                delete[] ptr_before;
                delete[] ptr_after;
            } catch (...) {
                std::cout << "\nProblems with remove element\n";
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

template<typename type>
void Set<type>::clear() {
    try {
        if (ptr != nullptr) {
            delete[] ptr;
            ptr = nullptr;
            size = 0;
        }
    } catch (...) {
        std::cout << "\nProblems with clear element\n";
    }
}

template<typename type>
ssize_t Set<type>::getSize() const {
    return size;
}

template<typename type>
Set<type> &Set<type>::operator=(const Set &set) {
    if (this != &set) {
        try {
            this->size = set.size;

            delete[] ptr;
            ptr = new type[size];

            for (ssize_t i = 0; i < size; ++i) {
                ptr[i] = set.ptr[i];
            }
        } catch (...) {
            std::cout << "\nProblems with constructor\n";
        }
    }
    return *this;
}

template<typename type>
Set<type>& Set<type>::operator=(Set &&set) noexcept {
    if (this != &set) {
        ptr = set.ptr;
        size = set.size;
        set.ptr = nullptr;
        set.size = NULL;
    }
    return *this;
}

template<typename type>
Set<type> Set<type>::operator*(const Set &set) {
    Set<type> new_set;

    if (getSize() >= set.getSize()) {
        for (ssize_t i = 0; i < getSize(); ++i) {
            if (set.find(ptr[i])) {
                new_set.add(ptr[i]);
            }
        }
    } else {
        for (ssize_t i = 0; i < set.getSize(); ++i) {
            if (find(set.ptr[i])) {
                new_set.add(ptr[i]);
            }
        }
    }
    return new_set;
}

template<typename type>
Set<type> Set<type>::operator+(const Set &set) {
    Set<type> new_set(*this);

    for (ssize_t i = 0; i < set.getSize(); ++i) {
        new_set.add(set.ptr[i]);
    }
    return new_set;
}

template<typename type>
Set<type> Set<type>::operator-(const Set &set) {
    Set temp_set = *this * set;
    Set new_set(*this);

    for (ssize_t i = 0; i < temp_set.getSize(); ++i) {
        if (find(temp_set.ptr[i])) {
            new_set.remove(temp_set.ptr[i]);
        }
    }
    return new_set;
}

template<typename type>
std::ostream& operator<<(std::ostream &stream, const Set<type> &set) {
    ssize_t count = 0;

    stream << "{ ";
    if (set.getSize() != 0) {
        for (ssize_t i = 0; i < set.size; ++i) {
            if (count == 0) {
                std::cout << static_cast<type>(set.ptr[i]);
            } else {
                std::cout << ", ";
                std::cout << static_cast<type>(set.ptr[i]);
            }
            ++count;
        }
    }
    stream << " }";
    return stream;
}
