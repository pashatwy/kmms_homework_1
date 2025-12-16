#ifndef SHELL_SORTING_HPP
#define SHELL_SORTING_HPP

#include <cstddef>

namespace gpi {
    int* generate_gaps_sequence(int array_size, int& sequence_size);
    void shell_sort(int* array, int array_size);
    void fill_random_values(int* array, int array_size);
}

#endif