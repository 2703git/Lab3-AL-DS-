#include <iostream>
#include <chrono>
#include <cstdlib>
using namespace std;
using namespace std::chrono;
//Problem 1
    // int arraySum(int A[], int n) {
    //     int sum = 0;
    //     for (int i = 0; i < n; i++) {
    //         sum += A[i];
    //     }
    //     return sum;
    // }
    // int main() {
    //     int n = 500000;
    //     int *A = new int[n];
    //     for (int i = 0; i < n; i++) {
    //         A[i] = rand();
    //     }
    //     auto start = high_resolution_clock::now();
    //     int result = arraySum(A, n);
    //     auto end = high_resolution_clock::now();
    //     auto duration = duration_cast<microseconds>(end - start);
    //     cout<<"Time taken: "<<duration.count()<<" microseconds"<<endl;
    //     delete [] A;
    //     return 0;
    // }

//Problem 2
// int linearSearch(int A[], int n, int key) {
//     for (int i = 0; i < n; i++) {
//         if (A[i] == key) return i;
//     }
//     return -1;
// }
// int main () {
//     int n = 20000;
//     int *A = new int[n];
//     for (int i = 0; i < n; i++) {
//         A[i] = rand();
//     }
//     auto start = high_resolution_clock::now();
//     linearSearch(A, n, A[0]);
//     auto end = high_resolution_clock::now();
//     auto duration = duration_cast<microseconds>(end - start);
//     cout<<"Best case: "<<duration.count()<<" microseconds"<<endl;
//
//     start = high_resolution_clock::now();
//     linearSearch(A, n, A[n/2]);
//     end = high_resolution_clock::now();
//     duration = duration_cast<microseconds>(end - start);
//     cout<<"Average case: "<<duration.count()<<" microseconds"<<endl;
//
//     start = high_resolution_clock::now();
//     linearSearch(A, n, 19999);
//     end = high_resolution_clock::now();
//     duration = duration_cast<microseconds>(end - start);
//     cout<<"Worst case: "<<duration.count()<<" microseconds"<<endl;
// }

//Problem 3
void bubbleSearch(int A[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (A[j] > A[j+1]) {
                int temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
            }
        }
    }
}
int main() {
    int n = 20000;
    int* A = new int[n];
    for (int i = 0; i < n; i++) {
        A[i] = rand();
    }
    auto start = high_resolution_clock::now();
    bubbleSearch(A, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<"Bubble Search Time: "<<duration.count()<<endl;
    delete [] A;
    return 0;
}
