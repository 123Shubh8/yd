#include <iostream>
#include <vector>
#include <omp.h>
#include <cstdlib>
#include <ctime> 
using namespace std;

// Sequential Bubble Sort
void sequential_bubble_sort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallel Bubble Sort using Odd-Even Transposition
void bubble_sort_odd_even(vector<int>& arr, int num_threads) {
    bool isSorted = false;
    int n = arr.size();
    omp_set_num_threads(num_threads);  // Set number of threads
    
    while (!isSorted) {
        isSorted = true;

        // Even phase
        #pragma omp parallel for
        for (int i = 0; i < n - 1; i += 2) {
            int tid = omp_get_thread_num();
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSorted = false;
                //#pragma omp critical
               // cout << "Thread " << tid << " swapped elements at indices " << i << " and " << i + 1 << " (even phase)\n";
            }
        }

        // Odd phase
        #pragma omp parallel for
        for (int i = 1; i < n - 1; i += 2) {
            int tid = omp_get_thread_num();
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSorted = false;
                //#pragma omp critical
                //cout << "Thread " << tid << " swapped elements at indices " << i << " and " << i + 1 << " (odd phase)\n";
            }
        }
    }
}

// Helper function to print array
void print_array(const vector<int>& arr) {
    for (int val : arr)
        cout << val << " ";
    cout << endl;
}

int main() {
    int size, num_threads;
    cout << "Enter the size of the array: ";
    cin >> size;
    cout << "Enter number of threads to use for parallel bubble sort: ";
    cin >> num_threads;

    srand(time(0));
    vector<int> original;
    for (int i = 0; i < size; ++i) {
        original.push_back(rand() % 1501);  // 0 to 1500
    }

    cout << "\nGenerated array:\n";
    print_array(original);

    double start, end;
    vector<int> arr1 = original;
    vector<int> arr2 = original;

    // Sequential Bubble Sort
    start = omp_get_wtime();
    sequential_bubble_sort(arr1);
    end = omp_get_wtime();
    cout << "\nSequential Bubble Sort Output:\n";
    print_array(arr1);
    cout << "Time: " << end - start << " seconds\n";

    // Parallel Bubble Sort (Odd-Even)
    start = omp_get_wtime();
    bubble_sort_odd_even(arr2, num_threads);
    end = omp_get_wtime();
    cout << "\nParallel Bubble Sort (Odd-Even) Output:\n";
    print_array(arr2);
    cout << "Time: " << end - start << " seconds\n";

    return 0;
}

