#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <string>

// Function to generate a random list of integers
std::vector<int> random_list(int length) {
    std::vector<int> arr(length);
    for (int i = 0; i < length; i++) {
        arr[i] = rand() % 1000;  // Generate random numbers from 0 to 999
    }
    return arr;
}

// Function to print a list of integers
void print_list(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// SelectionSort
void selection_sort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        std::swap(arr[i], arr[min_idx]);
    }
}

// InsertionSort
void insertion_sort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// BubbleSort
void bubble_sort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Function to measure the runtime of a sorting algorithm
template <typename Func>
double measure_runtime(Func sort_function, std::vector<int>& arr) {
    auto start = std::chrono::high_resolution_clock::now();
    sort_function(arr);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

int main() {
    std::vector<int> list_sizes = {10, 100, 1000, 10000, 100000};
    std::vector<double> selection_times;
    std::vector<double> insertion_times;
    std::vector<double> bubble_times;

    std::cout << "Starting the sorting measurements..." << std::endl;
    std::cout << std::endl;

    for (int size : list_sizes) {
        std::cout << "Generating random list of size " << size << std::endl;
        std::vector<int> original_list = random_list(size);
        std::cout << "Generated unsorted list: ";
        print_list(original_list);
        std::cout << std::endl;

        // SelectionSort
        std::vector<int> selection_list = original_list;
        std::cout << "Performing SelectionSort for list size " << size << std::endl;
        double selection_time = measure_runtime(selection_sort, selection_list);
        selection_times.push_back(selection_time);
        std::cout << "SelectionSort time: " << selection_time << " seconds" << std::endl;
        std::cout << "Sorted list: ";
        print_list(selection_list);
        std::cout << std::endl;

        // InsertionSort
        std::vector<int> insertion_list = original_list;
        std::cout << "Performing InsertionSort for list size " << size << std::endl;
        double insertion_time = measure_runtime(insertion_sort, insertion_list);
        insertion_times.push_back(insertion_time);
        std::cout << "InsertionSort time: " << insertion_time << " seconds" << std::endl;
        std::cout << "Sorted list: ";
        print_list(insertion_list);
        std::cout << std::endl;

        // BubbleSort
        std::vector<int> bubble_list = original_list;
        std::cout << "Performing BubbleSort for list size " << size << std::endl;
        double bubble_time = measure_runtime(bubble_sort, bubble_list);
        bubble_times.push_back(bubble_time);
        std::cout << "BubbleSort time: " << bubble_time << " seconds" << std::endl;
        std::cout << "Sorted list: ";
        print_list(bubble_list);
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Write sorting times to CSV file
    std::ofstream file("sorting_times.csv");
    if (!file.is_open()) {
        std::cerr << "Failed to open the file" << std::endl;
        return 1;
    }

    file << "List Size,Selection Sort Time,Insertion Sort Time,Bubble Sort Time\n";
    for (size_t i = 0; i < list_sizes.size(); i++) {
        file << list_sizes[i] << "," << selection_times[i] << "," << insertion_times[i] << "," << bubble_times[i] << "\n";
    }

    file.close();
    std::cout << "Sorting times written to sorting_times.csv" << std::endl;
    return 0;
}