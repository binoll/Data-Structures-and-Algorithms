// Copyright 2023 binoll
#pragma once

#include "../libs.hpp"

template<typename type>
class HashTable {
 public:
    HashTable() = default;

    HashTable(const uint64_t& hash_key, const type& value, const uint64_t& max_size);

    HashTable(const uint64_t& hash_key, const uint64_t& max_size);

    ~HashTable();

    uint64_t getSize() const;

    uint64_t getMaxSize() const;

    uint64_t findKey(const type& value);

    bool find(const type& value);

    void insert(const type& value);

    void remove(const type& value);

    template<typename new_type>
    friend std::ostream& operator<<(std::ostream& stream,
                                    const HashTable<new_type>& table);

 private:
    uint64_t hash(const type& value);

    type* arr;
    uint64_t max_size = 0;
    uint64_t size = 0;
    uint64_t hash_key = 0;
};

template<typename type>
HashTable<type>::HashTable(const uint64_t& hash_key, const type& value, const uint64_t& max_size) : hash_key(hash_key), max_size(max_size) {
    try {
        arr = new type[max_size];
        uint64_t key = hash(value);

        arr[key] = value;
        ++size;
    } catch (...) {
        std::cout << "Problems with constructor!\n";
    }

    for (uint64_t i = 0; i < max_size; ++i) {
        arr[i] = NULL;
    }
}

template<typename type>
HashTable<type>::HashTable(const uint64_t& hash_key, const uint64_t& max_size) : hash_key(hash_key), max_size(max_size) {
    try {
        arr = new type[max_size];
    }
    catch (...) {
        std::cout << "Problems with constructor!\n";
    }

    for (uint64_t i = 0; i < max_size; ++i) {
        arr[i] = NULL;
    }
}

template<typename type>
HashTable<type>::~HashTable() {
    try {
        if (size != 0) {
            delete[] arr;
            size = 0;
        }
        max_size = 0;
    } catch (...) {
        std::cout << "Problems with destructor\n!";
    }
}

template<typename type>
uint64_t HashTable<type>::getSize() const {
    return size;
}

template<typename type>
uint64_t HashTable<type>::getMaxSize() const {
    return max_size;
}

template<typename type>
uint64_t HashTable<type>::findKey(const type& value) {
    uint64_t key = hash(value);
    uint64_t key_find = key + 1;

    if (arr[key] == value) {
        return key;
    }

    while (key_find != key) {
        if (arr[key_find] == value) {
            return key_find;
        }
        ++key_find;

        key_find %= max_size;
    }
    return -1;
}


template<typename type>
bool HashTable<type>::find(const type& value) {
    uint64_t key = hash(value);
    uint64_t key_find = key + 1;

    if (arr[key] == value) {
        return true;
    }

    while (key_find != key) {
        if (arr[key_find] == value) {
            return true;
        }
        ++key_find;

        key_find %= max_size;
    }
    return false;
}

template<typename type>
void HashTable<type>::insert(const type& value) {
    try {
        if (size == max_size) {
            type* temp = arr;
            arr = new type[max_size * 2];
            size = 0;

            for (uint64_t i = 0; i < max_size; ++i) {
                arr[i] = NULL;
            }
            for (uint64_t i = 0; i < max_size - 1; ++i) {
                insert(temp[i]);
            }
            insert(value);
            return;
        }

        uint64_t key = hash(value);

        while (arr[key] != NULL) {
            ++key;
            key %= max_size;
        }
        arr[key] = value;
        ++size;
    } catch (...) {
        std::cout << "Problems with add method!\n";
    }
}

template<typename type>
void HashTable<type>::remove(const type& value) {
    uint64_t key = findKey(value);

    if (key == -1) {
        return;
    }

    arr[key] = NULL;
    --size;
}

template<typename type>
std::ostream& operator<<(std::ostream& stream,
                         const HashTable<type>& table) {
    std::cout << std::setw(10) << "Key" << std::setw(10) << "|" << std::setw(10) << "Value" << std::setw(10) << std::endl;
    std::cout << "-------------------|-------------------" << std::endl;
    for (uint64_t i = 0; i < table.max_size; ++i) {
        std::cout << std::setw(10) << i << std::setw(10) << "|" << std::setw(10) << table.arr[i] << std::setw(10) << std::endl;
    }

    return stream;
}

template<typename type>
uint64_t HashTable<type>::hash(const type& value) {
    return (std::hash<type>{}(value) + hash_key) % max_size;
}

/*Specialization for std::string*/
template<>
HashTable<std::string>::HashTable(const uint64_t& hash_key, const std::string& value, const uint64_t& max_size) : hash_key(hash_key), max_size(max_size) {
    try {
        arr = new std::string[max_size];
        uint64_t key = hash(value);

        arr[key] = value;
        ++size;
    } catch (...) {
        std::cout << "Problems with constructor!\n";
    }

    for (uint64_t i = 0; i < max_size; ++i) {
        arr[i] = "";
    }
}

template<>
HashTable<std::string>::HashTable(const uint64_t& hash_key, const uint64_t& max_size) : hash_key(hash_key), max_size(max_size) {
    try {
        arr = new std::string[max_size];
    }
    catch (...) {
        std::cout << "Problems with constructor!\n";
    }

    for (uint64_t i = 0; i < max_size; ++i) {
        arr[i] = "";
    }
}

template<>
void HashTable<std::string>::insert(const std::string& value) {
    try {
        if (size == max_size) {
            std::string* temp = arr;
            arr = new std::string[max_size * 2];
            size = 0;

            for (uint64_t i = 0; i < max_size; ++i) {
                arr[i] = "";
            }
            for (uint64_t i = 0; i < max_size - 1; ++i) {
                insert(temp[i]);
            }
            insert(value);

            max_size *= 2;
            return;
        }

        uint64_t key = hash(value);

        while (!arr[key].empty()) {
            ++key;
            key %= max_size;
        }
        arr[key] = value;
        ++size;
    } catch (...) {
        std::cout << "Problems with add method!\n";
    }
}

template<>
void HashTable<std::string>::remove(const std::string& value) {
    uint64_t key = findKey(value);

    if (key == -1) {
        return;
    }

    arr[key] = "";
    --size;
}
