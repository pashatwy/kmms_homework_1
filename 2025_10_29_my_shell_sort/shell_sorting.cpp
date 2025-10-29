#include <algorithm>
#include <ctime>
#include <random>

#include "shell_sorting.hpp"

size_t* generate_gaps_sequence(size_t array_size, size_t& sequence_size);
void shell_sort(int* array, size_t array_size);
void fill_random_values(int* array, size_t array_size);

namespace gpi {
    size_t* generate_gaps_sequence(size_t array_size, size_t& sequence_size) {
        const size_t MAX_SEQUENCE_SIZE = 100;
        size_t* sequence = new size_t[MAX_SEQUENCE_SIZE];
        sequence_size = 0;
        
        for (size_t p = 1; p <= array_size; p *= 2) {
            for (size_t q = p; q <= array_size; q *= 3) {
                if (sequence_size < MAX_SEQUENCE_SIZE) {
                    sequence[sequence_size++] = q;
                }
            }
        }
        
        for (size_t i = 0; i < sequence_size - 1; ++i) {
            for (size_t j = i + 1; j < sequence_size; ++j) {
                if (sequence[i] < sequence[j]) {
                    std::swap(sequence[i], sequence[j]);
                }
            }
        }
        
        size_t unique_count = 0;
        for (size_t i = 0; i < sequence_size; ++i) {
            if (i == 0 || sequence[i] != sequence[i - 1]) {
                sequence[unique_count++] = sequence[i];
            }
        }
        sequence_size = unique_count;
        
        return sequence;
    }

    void shell_sort(int* array, size_t array_size) {
        size_t gaps_size;
        size_t* gaps = generate_gaps_sequence(array_size, gaps_size);

        for (size_t gap_index = 0; gap_index < gaps_size; ++gap_index) {
            size_t gap = gaps[gap_index];
            for (size_t i = gap; i < array_size; ++i) {
                int temp_value = array[i];
                size_t j = i;

                while (j >= gap && array[j - gap] > temp_value) {
                    array[j] = array[j - gap];
                    j -= gap;
                }
                array[j] = temp_value;
            }
        }
        
        delete[] gaps;
    }

    void fill_random_values(int* array, size_t array_size) {
        std::mt19937 generator(std::time(nullptr));
        for (size_t i = 0; i < array_size; ++i) {
            array[i] = (generator() % 100) + 100;
        }
    }
}