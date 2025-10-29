#include <iostream>

#include "io.hpp"

namespace gpi {
    void print_array(const char* comment, const int* array, int array_size) {
        std::cout << comment;
        for (int i = 0; i < array_size; ++i) {
            std::cout << array[i] << ' ';
        }
        std::cout << std::endl;
    }
}