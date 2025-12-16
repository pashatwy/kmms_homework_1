#ifndef SHELL_SORTING_HPP
#define SHELL_SORTING_HPP

#include <cstddef>
#include <vector>

namespace gpi {
    void shell_sort(int* array, int array_size);
    
    void shell_sort(std::vector<int>& arr);

    int* generate_gaps_sequence(int array_size, int& sequence_size);
}

#endif