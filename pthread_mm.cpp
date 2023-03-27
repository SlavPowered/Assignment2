#include <iostream>
#include <pthread.h>
#include <chrono>
#include <random>

using namespace std;

#define M 600
#define N 200
#define P 900

int A[M][N];
int B[N][P];
int C[M][P] = { 0 };

struct args_struct {
    int row_start;
    int row_end;
};

void* matrixMultiply(void* args) {
    args_struct* my_args = (args_struct*)args;

    for (int i = my_args->row_start; i < my_args->row_end; i++) {
        for (int j = 0; j < P; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

int main() {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    const int num_threads = 6;
    pthread_t threads[num_threads];
    args_struct args[num_threads];
    
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
    // Create threads
    for (int i = 0; i < num_threads; i++) {
        args[i].row_start = (M / num_threads) * i;
        args[i].row_end = (M / num_threads) * (i + 1);
        pthread_create(&threads[i], NULL, matrixMultiply, (void*)&args[i]);
    }

    // Join threads
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
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
