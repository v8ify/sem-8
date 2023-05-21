#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    const int SIZE = 100;
    double* arr = (double*)malloc(sizeof(double) * SIZE);

    // Fill the array with random values
    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 100;
    }

    // Calculate min, max, sum, and average using parallel reduction
    double min = arr[0], max = arr[0], sum = 0.0;
    #pragma omp parallel for reduction(min:min) reduction(max:max) reduction(+:sum)
    for (int i = 0; i < SIZE; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
        if (arr[i] > max) {
            max = arr[i];
        }
        sum += arr[i];
    }

    double average = sum / SIZE;

    printf("Min: %f\n", min);
    printf("Max: %f\n", max);
    printf("Sum: %f\n", sum);
    printf("Average: %f\n", average);

    free(arr);
    return 0;
}