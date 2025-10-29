#ifndef SHELL_SORTING_HPP
#define SHELL_SORTING_HPP

#include <cstddef>

namespace gpi {
    size_t* generate_gaps_sequence(size_t array_size, size_t& sequence_size);
    void shell_sort(int* array, size_t array_size);
    void fill_random_values(int* array, size_t array_size);
}

#endif