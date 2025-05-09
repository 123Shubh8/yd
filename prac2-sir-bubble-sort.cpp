#include <iostream> 
#include <vector> 
#include <omp.h> 
using namespace std; 
void bubble_sort_odd_even(vector<int>& arr) { 
bool isSorted = false; 
while (!isSorted) { 
isSorted = true; 
#pragma omp parallel for 
for (int i = 0; i < arr.size() - 1; i += 2) { 
if (arr[i] > arr[i + 1]) { 
swap(arr[i], arr[i + 1]); 
isSorted = false; 
}   } 
#pragma omp parallel for 
for (int i = 1; i < arr.size() - 1; i += 2) { 
if (arr[i] > arr[i + 1]) { 
swap(arr[i], arr[i + 1]); 
isSorted = false; 
}   }   }   } 
void bubble_sort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        // Last i elements are already in place
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // Swap if current element is greater than next
                swap(arr[j], arr[j+1]);
            }
        }
    }
}
int main() { 
int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    vector<int> arr_seq = arr;
double start, end; 
// Measure performance of parallel bubble sort using odd- 
//even transposition 
start = omp_get_wtime(); 
bubble_sort_odd_even(arr);
end = omp_get_wtime(); 
cout << "Sorted Array :- "<< endl;
for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
cout << "Parallel bubble sort using odd-even transposition time: " << end - start << endl; 
start = omp_get_wtime(); 
bubble_sort(arr_seq);
end = omp_get_wtime(); 
cout << "Sorted Array :- "<< endl;
for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
cout << "Sequential bubble sort  time: " << end - start << endl; 
}