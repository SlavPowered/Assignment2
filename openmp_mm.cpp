#include <iostream>
#include <chrono>
#include <omp.h>

using namespace std;

#define M 600
#define N 200
#define P 900

int A[M][N]; 
int B[N][P];
int C[M][P] = { 0 };


void matrixMultiply() {
    
#pragma omp parallel for num_threads(6)
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            A[i][j] = rand() % 1000;
        }
    }
    
    for(int i = 0; i < N; i++){
        for(int j = 0; j < P; j++){
            B[i][j] = rand() % 1000;
        }
    }
    auto t1 = high_resolution_clock::now();
    matrixMultiply();
    auto t2 = high_resolution_clock::now();
    
    duration<double, std::milli> ms_double = t2 - t1; 
    // Print result
    /* for (int i = 0; i < M; i++) { */
    /*     for (int j = 0; j < P; j++) { */
    /*         cout << C[i][j] << " "; */
    /*     } */
    /*     cout << endl; */
    /* } */
    cout<<"-------------------\n";
    cout<<"Execution time: "<<ms_double.count() << "ms\n";
    return 0;
}
