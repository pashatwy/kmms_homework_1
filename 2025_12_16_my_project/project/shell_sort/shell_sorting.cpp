#include <algorithm>
#include <ctime>
#include <random>

#include "shell_sorting.hpp"

namespace gpi {
    int* generate_gaps_sequence(int array_size, int& sequence_size) {
        const int max_sequence_size = 100;
        int* sequence = new int[max_sequence_size];
        sequence_size = 0;
        
        for (int p = 1; p <= array_size; p *= 2) {
            for (int q = p; q <= array_size; q *= 3) {
                if (sequence_size < max_sequence_size) {
                    sequence[sequence_size++] = q;
                }
            }
        }
        
        for (int i = 0; i < sequence_size - 1; ++i) {
            for (int j = i + 1; j < sequence_size; ++j) {
                if (sequence[i] < sequence[j]) {
                    std::swap(sequence[i], sequence[j]);
                }
            }
        }
        
        int unique_count = 0;
        for (int i = 0; i < sequence_size; ++i) {
            if (i == 0 || sequence[i] != sequence[i - 1]) {
                sequence[unique_count++] = sequence[i];
            }
        }
        sequence_size = unique_count;
        
        return sequence;
    }

    void shell_sort(int* array, int array_size) {
        int gaps_size;
        int* gaps = generate_gaps_sequence(array_size, gaps_size);

        for (int gap_index = 0; gap_index < gaps_size; ++gap_index) {
            int gap = gaps[gap_index];
            for (int i = gap; i < array_size; ++i) {
                int temp_value = array[i];
                int j = i;

                while (j >= gap && array[j - gap] > temp_value) {
                    array[j] = array[j - gap];
                    j -= gap;
                }
                array[j] = temp_value;
            }
        }
        
        delete[] gaps;
    }

    void fill_random_values(int* array, int array_size) {
        std::mt19937 generator(std::time(nullptr));
        for (int i = 0; i < array_size; ++i) {
            array[i] = (generator() % 100) + 100;
        }
    }
}