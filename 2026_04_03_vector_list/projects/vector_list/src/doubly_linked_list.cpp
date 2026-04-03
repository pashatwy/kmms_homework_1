#include "doubly_linked_list.hpp"
#include <iostream>

using biv::DoublyLinkedList;

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    Node* current = this->begin;
    while (current != nullptr) {
        Node* next_node = current->next;
        delete current;
        current = next_node;
    }
}

template<typename T>
std::size_t DoublyLinkedList<T>::get_size() const noexcept {
    return this->size;
}

template<typename T>
bool DoublyLinkedList<T>::has_item(const T& value) const noexcept {
    Node* current = this->begin;
    while (current != nullptr) {
        if (current->value == value) return true;
        current = current->next;
    }
    return false;
}

template<typename T>
void DoublyLinkedList<T>::print() const noexcept {
    Node* current = this->begin;
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template<typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
    Node* new_node = new Node(value);
    new_node->prev = this->end;
    
    if (this->end != nullptr) {
        this->end->next = new_node;
    } else {
        this->begin = new_node;
    }
    
    this->end = new_node;
    this->size++;
}

template<typename T>
bool DoublyLinkedList<T>::remove_first(const T& value) noexcept {
    Node* current = this->begin;
    
    while (current != nullptr) {
        if (current->value == value) {
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            } else {
                this->begin = current->next;
            }
            
            if (current->next != nullptr) {
                current->next->prev = current->prev;
            } else {
                this->end = current->prev;
            }
            
            delete current;
            this->size--;
            return true;
        }
        current = current->next;
    }
    return false;
}