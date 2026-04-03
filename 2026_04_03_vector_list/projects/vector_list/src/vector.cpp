#include "vector.hpp"
#include <iostream>

using biv::Vector;

template<typename T>
const std::size_t Vector<T>::START_CAPACITY = 10;

template<typename T>
Vector<T>::Vector() {
    this->capacity = START_CAPACITY;
    this->arr = new T[this->capacity];
    this->size = 0;
}

template<typename T>
Vector<T>::~Vector() {
    delete[] this->arr;
}

template<typename T>
std::size_t Vector<T>::get_size() const noexcept {
    return this->size;
}

template<typename T>
bool Vector<T>::has_item(const T& value) const noexcept {
    for (std::size_t i = 0; i < this->size; i++) {
        if (this->arr[i] == value) return true;
    }
    return false;
}

template<typename T>
bool Vector<T>::insert(const std::size_t position, const T& value) {
    if (position > this->size) return false;

    if (this->size >= this->capacity) {
        std::size_t new_cap = this->capacity * 2;
        T* new_arr = new T[new_cap];

        for (std::size_t i = 0; i < position; i++)
            new_arr[i] = this->arr[i];
        
        new_arr[position] = value;

        for (std::size_t i = position; i < this->size; i++)
            new_arr[i + 1] = this->arr[i];

        delete[] this->arr;
        this->arr = new_arr;
        this->capacity = new_cap;
        this->size++;
        return true;
    }

    for (std::size_t i = this->size; i > position; i--) {
        this->arr[i] = this->arr[i - 1];
    }
    this->arr[position] = value;
    this->size++;
    return true;
}

template<typename T>
void Vector<T>::print() const noexcept {
    for (std::size_t i = 0; i < this->size; i++)
        std::cout << this->arr[i] << (i == this->size - 1 ? "" : " ");
    std::cout << std::endl;
}

template<typename T>
void Vector<T>::push_back(const T& value) {
    this->insert(this->size, value);
}

template<typename T>
bool Vector<T>::remove_first(const T& value) {
    for (std::size_t i = 0; i < this->size; i++) {
        if (this->arr[i] == value) {
            for (std::size_t j = i; j < this->size - 1; j++)
                this->arr[j] = this->arr[j + 1];
            this->size--;

            if (this->size > 0 && this->size <= this->capacity / 4 && this->capacity / 2 >= START_CAPACITY) {
                std::size_t new_cap = this->capacity / 2;
                T* new_arr = new T[new_cap];
                for (std::size_t k = 0; k < this->size; k++)
                    new_arr[k] = this->arr[k];
                delete[] this->arr;
                this->arr = new_arr;
                this->capacity = new_cap;
            }
            return true;
        }
    }
    return false;
}