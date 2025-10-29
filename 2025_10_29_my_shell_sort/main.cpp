#include "io.hpp"
#include "shell_sorting.hpp"

#include <iostream>

int main() {
    size_t array_size;
    std::cout << "Введите длину массива: " << std::endl;
    std::cin >> array_size;
    
    int* array = new int[array_size];
    gpi::fill_random_values(array, array_size);
    
    gpi::print_array("Массив до сортировки: ", array, array_size);
    gpi::shell_sort(array, array_size);
    gpi::print_array("Массив после сортировки: ", array, array_size);
    
    delete[] array;
    return 0;
}