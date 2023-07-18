// Copyright 2023 binoll
#pragma once

#include "../libs.hpp"

template<typename type>
class Set {
 public:
    Set() = default;  // constructor without parameters

    explicit Set(const type& value);  // constructor with parameters

    Set(const Set& set);  // copy constructor

    Set(Set&& set) noexcept;  // move constructor

    ~Set();  // destructor

    bool find(const type& value) const;  // item search, return bool

    int64_t findIndex(const type& value) const;  // return index (if element is not in set then -1)

    bool add(const type& value);  // adding an element to a set

    bool remove(const type& value);  // removing an element from a set

    void clear();  // clear set

    int64_t getSize() const;  // method returns current size of the set

    Set<type>& operator=(const Set<type>& set);  // overloading for assignment

    Set<type>& operator=(Set<type>&& set) noexcept;  // for assignment with carry

    Set<type> operator*(const Set<type>& set);  // for the intersection of two sets

    Set<type> operator+(const Set<type>& set);  // for combining two sets

    Set<type> operator-(const Set<type>& set);  // for the difference of two sets

    Set<type> operator^(const Set<type>& set);  // for the symmetric difference of two sets

    template<typename new_type>
    friend std::ostream& operator<<(std::ostream& stream,
                                    const Set<new_type>& set);  // for print

 private:
    int64_t size = 0;  // current capacity of the set
    int64_t max_size = std::numeric_limits<int64_t>::max();  // maximum value
    type* arr = nullptr;  // indicates the array in which the elements of the set are stored
};

template<typename type>
Set<type>::Set(const type& value) {
    try {
        arr = new type[++size];
        arr[size - 1] = value;
    } catch (...) {
        std::cout << "\nProblems with constructor\n";
    }
}

template<typename type>
Set<type>::Set(const Set<type>& set) {
    try {
        this->size = set.size;

        if (set.size == 0) {
            delete[] arr;
            arr = nullptr;
        } else {
            delete[] arr;
            arr = new type[size];

            for (int64_t i = 0; i < size; ++i) {
                arr[i] = set.arr[i];
            }
        }
    } catch (...) {
        std::cout << "\nProblems with copy constructor\n";
    }
}

template<typename type>
Set<type>::Set(Set<type>&& set) noexcept {
    if (this != &set) {
        arr = set.arr;
        size = set.size;
        set.arr = nullptr;
        set.size = 0;
    }
}

template<typename type>
Set<type>::~Set() {
    try {
        delete[] arr;
        arr = nullptr;
        size = 0;
    } catch (...) {
        std::cout << "\nProblems with destructor\n";
    }
}

template<typename type>
bool Set<type>::find(const type& value) const {
    for (int64_t i = 0; i < size; ++i) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}

template<typename type>
int64_t Set<type>::findIndex(const type& value) const {
    for (int64_t i = 0; i < size; ++i) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}

template<typename type>
bool Set<type>::add(const type& value) {
    if (size == max_size) {
        std::cout << "\nProblems with add element, no memory!\n";
        return false;
    } else if (findIndex(value) == -1) {
        try {
            if (arr == nullptr) {
                int64_t index = size;

                ++size;
                arr = new type[size];
                arr[index] = value;
            } else {
                type *new_ptr = arr;
                int64_t index = size;

                ++size;
                arr = nullptr;
                arr = new type[size];
                for (int64_t i = 0; i < index; ++i) {
                    arr[i] = new_ptr[i];
                }
                arr[index] = value;
                delete[] new_ptr;
            }
        } catch (...) {
            std::cout << "\nProblems with add element\n";
            return false;
        }
        return true;
    } else {
        return false;
    }
}

template<typename type>
bool Set<type>::remove(const type& value) {
    int64_t index = findIndex(value);
    int64_t size_after = size - (index + 1);
    int64_t size_before = index;

    if (index != -1) {
        try {
            if (size == 1) {
                --size;
                delete[] arr;
                arr = nullptr;
            } else if (size_before == 0) {
                type *arr_after = new type[size_after];

                for (int64_t i = 0, count = (size_before + 1); count < size; ++count, ++i) {
                    arr_after[i] = arr[count];
                }

                --size;
                delete[] arr;
                arr = new type[size];

                for (int64_t i = 0, count = size_before; i < size_after; ++count, ++i) {
                    arr[count] = arr_after[i];
                }
                delete[] arr_after;
            } else if (size_after == 0) {
                type *arr_before = new type[size_before];

                for (int64_t count = 0; count < size_before; ++count) {
                    arr_before[count] = arr[count];
                }

                --size;
                delete[] arr;
                arr = new type[size];

                for (int64_t count = 0; count < size_before; ++count) {
                    arr[count] = arr_before[count];
                }
                delete[] arr_before;
            } else {
                type *ptr_before = new type[size_before];
                type *ptr_after = new type[size_after];

                for (int64_t count = 0; count < size_before; ++count) {
                    ptr_before[count] = arr[count];
                }
                for (int64_t i = 0, count = (size_before + 1); count < size; ++count, ++i) {
                    ptr_after[i] = arr[count];
                }

                --size;
                delete[] arr;
                arr = new type[size];

                for (int64_t count = 0; count < size_before; ++count) {
                    arr[count] = ptr_before[count];
                }
                for (int64_t i = 0, count = size_before; i < size_after; ++count, ++i) {
                    arr[count] = ptr_after[i];
                }
                delete[] ptr_before;
                delete[] ptr_after;
            }
        } catch (...) {
            std::cout << "\nProblems with remove element\n";
            return false;
        }
        return true;
    } else {
        return false;
    }
}

template<typename type>
void Set<type>::clear() {
    try {
        delete[] arr;
        arr = nullptr;
        size = 0;
    } catch (...) {
        std::cout << "\nProblems with clear element\n";
    }
}

template<typename type>
int64_t Set<type>::getSize() const {
    return size;
}

template<typename type>
Set<type>& Set<type>::operator=(const Set<type>& set) {
    if (this != &set) {
        try {
            this->size = set.size;

            delete[] arr;
            arr = new type[size];

            for (int64_t i = 0; i < size; ++i) {
                arr[i] = set.arr[i];
            }
        } catch (...) {
            std::cout << "\nProblems with constructor\n";
        }
    }
    return *this;
}

template<typename type>
Set<type>& Set<type>::operator=(Set<type>&& set) noexcept {
    if (this != &set) {
        arr = set.arr;
        size = set.size;
        set.arr = nullptr;
        set.size = NULL;
    }
    return *this;
}

template<typename type>
Set<type> Set<type>::operator*(const Set<type>& set) {
    Set<type> new_set;

    if (getSize() > set.getSize()) {
        for (int64_t i = 0; i < getSize(); ++i) {
            if (set.find(arr[i])) {
                new_set.add(arr[i]);
            }
        }
    } else {
        for (int64_t i = 0; i < set.getSize(); ++i) {
            if (find(set.arr[i])) {
                new_set.add(set.arr[i]);
            }
        }
    }
    return new_set;
}

template<typename type>
Set<type> Set<type>::operator+(const Set<type>& set) {
    Set<type> new_set(*this);

    for (int64_t i = 0; i < set.getSize(); ++i) {
        new_set.add(set.arr[i]);
    }
    return new_set;
}

template<typename type>
Set<type> Set<type>::operator-(const Set<type>& set) {
    Set temp_set = *this * set;
    Set new_set(*this);

    for (int64_t i = 0; i < temp_set.getSize(); ++i) {
        if (find(temp_set.arr[i])) {
            new_set.remove(temp_set.arr[i]);
        }
    }
    return new_set;
}

template<typename type>
Set<type> Set<type>::operator^(const Set<type>& set) {
    Set new_set = (*this + set) - (*this * set);
    return new_set;
}

template<typename type>
std::ostream& operator<<(std::ostream& stream, const Set<type>& set) {
    int64_t count = 0;

    stream << "{ ";
    if (set.size != 0) {
        for (int64_t i = 0; i < set.size; ++i) {
            if (count == 0) {
                stream << static_cast<type>(set.arr[i]);
            } else {
                stream << ", ";
                stream << static_cast<type>(set.arr[i]);
            }
            ++count;
        }
    }
    stream << " }";
    return stream;
}
